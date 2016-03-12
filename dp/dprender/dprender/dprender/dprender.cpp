
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
#include "../dprender_scene/dprender_scene.h"
#include "../dprender_scene/dprender_scene_ref.h"
#include "../../../dpdefines.h"

#if defined dprender_debug
#include <iostream>
#endif // defined

namespace dp
{

    //ctor
    dprender::dprender( dpapi_factory *wf ) : dptask( "Renderer Main", 3 )
    {
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


        if( this->frametask )
            delete this->frametask;
        if( this->cl_a )
            delete this->cl_a;
        if( this->cl_b )
            delete this->cl_b;

        this->deleteScenes();

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
                return 0;
            g.release( apil );
        }

        if( !dprender::waitForFlag( this->flag_next, 1, 10, tl ) )
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

        if( this->api )
            delete this->api;
        this->api = 0;

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

    bool __helper_makeScene( dprender_scenelink_clist *p, dpapi_writelock *al )
    {
        p->clists.a.cl = 0;
        p->clists.a.b = 0;
        p->clists.b.cl = 0;
        p->clists.b.b = 0;
        p->clists.consumer.pnext = &p->clists.a;
        p->clists.consumer.pprev = &p->clists.b;
        p->clists.creator = p->clists.consumer;

        return ( p->clists.a.cl !=0 ) && ( p->clists.b.cl != 0 );
    }

    //make scene
    dprender_scene *dprender::makeScene( dprender_writelock *wl )
    {
        dprender_scene *r;
        dprender_scene_ref *rr;
        unsigned int i;
        dpapi_writelock *al;
        dpshared_guard g;
        dprender_scenelink *p, *f;
        bool b;

        for( i = 0, f = 0; i < dprender_scenelink_MAX; i++ )
        {
            p = &this->scenes.scenes[ i ];
            if( p->bAlive )
                continue;
            f = p;
        }

        al = (dpapi_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->api, 1000 );
        if( !al )
            return 0;

        b = __helper_makeScene( &f->guis, al );
        b &= __helper_makeScene( &f->sky, al );
        b &= __helper_makeScene( &f->terrain, al );
        b &= __helper_makeScene( &f->models, al );
        if( !b )
            return 0;

        r = new dprender_scene( wl );
        if( !r )
            return 0;
        rr = (dprender_scene_ref *)this->clg.getRef( r );
        if( !rr )
        {
            delete r;
            return r;
        }

        f->rscene = rr;
        f->bAlive = 1;

        return r;
    }

    void __helper_zeroScenes( dprender_scenelink_clist *p )
    {
        p->clists.a.cl = 0;
        p->clists.a.b = 0;
        p->clists.b.cl = 0;
        p->clists.b.b = 0;
        p->clists.consumer.pnext = &p->clists.a;
        p->clists.consumer.pprev = &p->clists.b;
        p->clists.creator = p->clists.consumer;
    }

    //zero out scenes
    void dprender::zeroScenes( void )
    {
        dprender_scenelink *p;
        unsigned int i;

        for( i = 0; i < dprender_scenelink_MAX; i++ )
        {
            p = &this->scenes.scenes[ i ];

            p->bAlive = 0;
            p->rscene = 0;

            __helper_zeroScenes( &p->guis );
            __helper_zeroScenes( &p->sky );
            __helper_zeroScenes( &p->terrain );
            __helper_zeroScenes( &p->models );
        }
    }

    void __helper_deleteScenes( dprender_scenelink_clist *p )
    {
        if( p->clists.a.cl )
            delete p->clists.a.cl;
        if( p->clists.b.cl )
            delete p->clists.b.cl;
    }

    //delete scenes
    void dprender::deleteScenes( void )
    {
        dprender_scenelink *p;
        unsigned int i;
        dprender_scene_ref *rr;

        for( i = 0; i < dprender_scenelink_MAX; i++ )
        {
            p = &this->scenes.scenes[ i ];

            rr = p->rscene;
            if( rr )
                this->clg.release( rr );

            __helper_deleteScenes( &p->guis );
            __helper_deleteScenes( &p->sky );
            __helper_deleteScenes( &p->terrain );
            __helper_deleteScenes( &p->models );
        }

        this->zeroScenes();
    }

}







