
/*

*/

#include "dprender.h"
#include "dprender_ref.h"
#include "dprender_readlock.h"
#include "dprender_writelock.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"
#include "../../dpapi/dpapi/dpapi/dpapi_factory.h"
#include "../../dpapi/dpapi/dpapi/dpapi.h"
#include "../../dpapi/dpapi/dpapi/dpapi_writelock.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi/dpapi_primary_commandlist/dpapi_primary_commandlist.h"
#include "../../dpapi/dpapi/dpapi_primary_commandlist/dpapi_primary_commandlist_writelock.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist_writelock.h"
#include "../dprender_frame_thread/dprender_frame_thread.h"
#include "../dprender_frame_thread/dprender_frame_thread_writelock.h"
#include "../dprender_scene/dprender_scene.h"
#include "../dprender_scene/dprender_scene_readlock.h"
#include "../dprender_scene/dprender_scene_writelock.h"
#include "../../../dpdefines.h"
#include "../../../dpgfx/dpgfx/dpgfx.h"
#include "../../../dpgfx/dpgfx/dpgfx_readlock.h"

#if defined dprender_debug
#include <iostream>
#endif // defined

namespace dp
{

    //ctor
    dprender::dprender( dpgfx *gfx, dpapi_factory *wf ) : dptask( "Renderer Main", dp_rendertask_sleeptime )
    {
        this->gfx = gfx;
        this->apifactory = wf;
        this->api = 0;
        this->main_ctx = this->frame_ctx = 0;
        this->cl_a = this->cl_b = 0;
        this->flag_a = this->flag_b = 0;
        this->frametask = 0;
        this->fps = 0;
        this->f_last_t = 0;
        this->t_last_f = 0;
        this->zeroScenes();
    }

    //dtor
    dprender::~dprender( void )
    {
        this->deleteScenes();

        this->waitForStop();
        this->unlink();

        if( this->frametask )
            delete this->frametask;
        if( this->cl_a )
            delete this->cl_a;
        if( this->cl_b )
            delete this->cl_b;

        if( this->main_ctx )
            delete this->main_ctx;
        if( this->frame_ctx )
            delete this->frame_ctx;

        if( this->api )
            delete this->api;
        delete this->apifactory;
    }

    //generate readlock
    dpshared_readlock *dprender::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_ref( this, k, t_sync );
    }

    //override to do task execution
    bool dprender::onTaskRun( dptask_writelock *tl )
    {
        dpapi_primary_commandlist_writelock *cll;
        dpapi_primary_commandlist *pcl;
        dpapi_context_writelock *ctxl;
        std::atomic<bool> *pflag;
        dpshared_guard g;
        dpapi_writelock *apil;
        uint64_t tn;

        apil = (dpapi_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->api, 3 );
        if( apil )
        {
            apil->run();
            if( !apil->isOpen() )
            {
                this->stop();
                return 1;
            }
            g.release( apil );
        }

        if( !( *this->flag_next ) )
            return 1;

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->main_ctx, 30 );
        if( !ctxl )
            return 1;

        cll = (dpapi_primary_commandlist_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->cl_next, 30 );
        if( !cll )
            return 1;

        cll->execute( ctxl );
        ( *this->flag_next ) = 0;

        pcl = this->cl_next;
        pflag = this->flag_next;

        this->cl_next = this->cl_prev;
        this->flag_next = this->flag_prev;

        this->cl_prev = pcl;
        this->flag_prev = pflag;

        tn = this->getTicks();
        this->f_last_t++;
        if( this->t_last_f + 100 < tn )
        {
            this->fps = this->f_last_t * 10;
            this->t_last_f = tn;
            this->f_last_t = 0;
        }

#if defined dprender_debug
        std::cout << "Render Main: Primary command buffer executed. Frame presented. " << this->fps <<" FPS\r\n";
#endif // defined

        if( tn - this->t_last_clone > 500 )
        {
            this->cloneScenes();
            this->removeOldScenes();
            this->t_last_clone = tn;
        }

        return 1;
    }

    //override to do task startup
    bool dprender::onTaskStart( dptask_writelock *tl )
    {
        dpshared_guard g;
        dpapi_writelock *apil;
        dpapi_context_writelock *ctxl;

        if( !this->apifactory )
            return 0;

        this->api = this->apifactory->makeApi();
        if( !this->api )
            return 0;

        apil = (dpapi_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->api, 1000 );
        if( !apil )
            return 0;

        apil->run();

        this->main_ctx = apil->makeContext();
        this->frame_ctx = apil->makeContext();

        g.release( apil );
        if( !this->main_ctx || !this->frame_ctx )
            return 0;

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->main_ctx, 1000 );
        if( !ctxl )
            return 0;

        this->cl_a = ctxl->makePrimaryCommandList();
        this->cl_b = ctxl->makePrimaryCommandList();

        g.release( ctxl );
        if( !this->cl_a || !this->cl_b )
            return 0;

        this->flag_a = this->flag_b = 0;
        this->cl_next = this->cl_a;
        this->flag_next = &this->flag_a;
        this->cl_prev = this->cl_b;
        this->flag_prev = &this->flag_b;

        this->frametask = new dprender_frame_thread( this->frame_ctx, this->cl_a, this->cl_b, &this->flag_a, &this->flag_b );
        if( !this->frametask )
            return 0;

        if( !this->addStaticTask( this->frametask, 1 ) )
            return 0;

#if defined dprender_debug
        std::cout << "Render Main: Started.\r\n";
#endif // defined

        return 1;
    }

    //override to do task shutdown
    bool dprender::onTaskStop( dptask_writelock *tl )
    {
        if( !this->stopScenes() )
            return 0;

        if( !dptask::stopAndDelete( (dptask **)&this->frametask ) )
            return 0;

        if( this->cl_a )
            delete this->cl_a;
        this->cl_a = 0;
        if( this->cl_b )
            delete this->cl_b;
        this->cl_b = 0;

        if( this->main_ctx )
            delete this->main_ctx;
        this->main_ctx = 0;
        if( this->frame_ctx )
            delete this->frame_ctx;
        this->frame_ctx = 0;

//        if( this->api )
  //          delete this->api;
    //    this->api = 0;

#if defined dprender_debug
        std::cout << "Render Main: Stopped.\r\n";
#endif // defined

        return 1;
    }

    //wait for flag to set or unset
    bool dprender::waitForFlag( std::atomic<bool> *f, bool m, unsigned int wait_ms, dptask_writelock *l )
    {
        uint64_t w, ts, tn, te;

        if( *f == m )
            return 1;

        ts = tn = l->getTicks();
        w = wait_ms;
        te = ts + w;

        while( tn < te )
        {
            if( *f == m )
                return 1;
            tn = l->getTicks();
        }

        return 0;
    }

    //clone new scenes
    void dprender::cloneScenes( void )
    {
        dpscene *gscenes[ dprender_max_scenes ];
        dpscene *s;
        dpgfx_readlock *gl;
        dpshared_guard g;
        unsigned int i, e;

        gl = (dpgfx_readlock *)dpshared_guard_tryReadLock_timeout( g, this->gfx, 100 );
        if( !gl )
            return;

        e = gl->getScenes( gscenes, dprender_max_scenes );
        g.release( gl );

        for( i = 0; i < e; i++ )
        {
            s = gscenes[ i ];
            if( !s )
                continue;
            if( this->findScene( s ) )
                continue;
            this->addScene( s );
        }
    }

    //look for scene
    dprender_scene *dprender::findScene( dpscene *s )
    {
        unsigned int i;
        dprender_scene *p;
        dprender_scene_readlock *pl;
        dpshared_guard g;

        for( i = 0; i < dprender_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;
            pl = (dprender_scene_readlock *)dpshared_guard_tryReadLock_timeout( g, p, 1000 );
            if( !pl )
                continue;
            if( pl->hasScene( s ) )
                return p;
            g.release( pl );
        }

        return 0;
    }

    //add new scene
    dprender_scene *dprender::addScene( dpscene *s )
    {
        unsigned int i;
        dprender_scene *p;
        dpshared_guard g;
        dprender_frame_thread_writelock *tl;

        for( i = 0; i < dprender_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( p )
                continue;
            p = new dprender_scene( s, this->api, this );
            if( !p )
                return 0;

            tl = (dprender_frame_thread_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->frametask, 1000 );
            if( !tl )
            {
                delete p;
                return 0;
            }

            if( !tl->addScene( p ) )
            {
                delete p;
                return 0;
            }

            g.release( tl );

            this->scenes[ i ] = p;
            this->addStaticTask( p, 1 );

            return p;
        }

        return 0;
    }

    //remove old scenes
    void dprender::removeOldScenes( void )
    {
        unsigned int i;
        dprender_scene *p;
        dprender_scene_writelock *pl;
        dpshared_guard g;

        for( i = 0; i < dprender_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;
            pl = (dprender_scene_writelock *)dpshared_guard_tryWriteLock_timeout( g, p, 10 );
            if( !pl )
                continue;
            if( pl->isRun() )
            {
                g.release( pl );
                continue;
            }
            g.release( pl );

            delete p;
            this->scenes[ i ] = 0;
        }
    }

    //stop scenes
    bool dprender::stopScenes( void )
    {
        unsigned int i;
        dprender_scene *p;
        dprender_scene_writelock *pl;
        dpshared_guard g;
        dprender_frame_thread_writelock *tl;
        bool r;

        r = 0;
        for( i = 0; i < dprender_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;

            tl = (dprender_frame_thread_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->frametask, 10 );
            if( tl )
                tl->removeScene( p );
            g.release( tl );

            pl = (dprender_scene_writelock *)dpshared_guard_tryWriteLock_timeout( g, p, 10 );
            if( !pl )
                continue;
            r |= pl->isRun();
            pl->stop();

            g.release( pl );
        }

        return !r;
    }

    //delete scenes
    void dprender::deleteScenes( void )
    {
        unsigned int i;
        dprender_scene *p;

        for( i = 0; i < dprender_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;
            delete p;
        }

        this->zeroScenes();
    }

    //zero scenes
    void dprender::zeroScenes( void )
    {
        unsigned int i;

        for( i = 0; i < dprender_max_scenes; i++ )
            this->scenes[ i ] = 0;
    }

}







