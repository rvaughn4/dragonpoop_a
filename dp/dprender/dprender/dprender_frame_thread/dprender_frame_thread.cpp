
/*

*/

#include "dprender_frame_thread.h"
#include "dprender_frame_thread_ref.h"
#include "dprender_frame_thread_readlock.h"
#include "dprender_frame_thread_writelock.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"
#include "../../dpapi/dpapi/dpapi/dpapi_factory.h"
#include "../../dpapi/dpapi/dpapi/dpapi.h"
#include "../../dpapi/dpapi/dpapi/dpapi_writelock.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi/dpapi_primary_commandlist/dpapi_primary_commandlist.h"
#include "../../dpapi/dpapi/dpapi_primary_commandlist/dpapi_primary_commandlist_writelock.h"
#include "../dprender/dprender.h"
#include "../../../dpdefines.h"
#include "../dprender_scene/dprender_scene_writelock.h"
#include "../dprender_scene/dprender_scene.h"
#include "../dprender_scene/dprender_scene_ref.h"

#if defined dprender_debug
#include <iostream>
#endif // defined

namespace dp
{

    //ctor
    dprender_frame_thread::dprender_frame_thread( dpapi_context *ctx, dpapi_primary_commandlist *cl_a, dpapi_primary_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b ) : dptask( "Renderer Frame", 3 )
    {
        this->ctx = ctx;
        this->cl_a = cl_a;
        this->cl_b = cl_b;
        this->flag_a = flag_a;
        this->flag_b = flag_b;
        this->cl_next = this->cl_a;
        this->cl_prev = this->cl_b;
        this->flag_next = this->flag_a;
        this->flag_prev = this->flag_b;

        this->zeroScenes();
    }

    //dtor
    dprender_frame_thread::~dprender_frame_thread( void )
    {
        this->waitForStop();
        this->deleteScenes();
        this->unlink();
    }

    //generate readlock
    dpshared_readlock *dprender_frame_thread::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_frame_thread_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender_frame_thread::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_frame_thread_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender_frame_thread::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_frame_thread_ref( this, k, t_sync );
    }

    //override to do task execution
    bool dprender_frame_thread::onTaskRun( dptask_writelock *tl )
    {
        dpapi_primary_commandlist_writelock *cll;
        dpapi_primary_commandlist *pcl;
        dpapi_context_writelock *ctxl;
        std::atomic<bool> *pflag;
        dpshared_guard g;

        if( ( *this->flag_next ) )
            return 1;

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->ctx, 30 );
        if( !ctxl )
            return 1;

        cll = (dpapi_primary_commandlist_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->cl_next, 30 );
        if( !cll )
            return 1;

        if( !cll->clearAndRecord( ctxl ) )
            return 1;

#if defined dprender_debug
        std::cout << "Render Frame: Primary command buffer cleared.\r\n";
#endif // defined

        cll->clearColor( ctxl, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX );
        cll->clearDepth( ctxl, 1 );

        this->drawScenes( ctxl, cll );

        cll->swapBuffers( ctxl );

        if( !cll->compile( ctxl ) )
            return 1;

        ( *this->flag_next ) = 1;

        pcl = this->cl_next;
        pflag = this->flag_next;

        this->cl_next = this->cl_prev;
        this->flag_next = this->flag_prev;

        this->cl_prev = pcl;
        this->flag_prev = pflag;

#if defined dprender_debug
        std::cout << "Render Frame: Primary command buffer compiled.\r\n";
#endif // defined

        return 1;
    }

    //override to do task startup
    bool dprender_frame_thread::onTaskStart( dptask_writelock *tl )
    {
#if defined dprender_debug
        std::cout << "Render Frame: Started.\r\n";
#endif // defined
        return 1;
    }

    //override to do task shutdown
    bool dprender_frame_thread::onTaskStop( dptask_writelock *tl )
    {
        this->deleteScenes();

#if defined dprender_debug
        std::cout << "Render Frame: Stopped.\r\n";
#endif // defined
        return 1;
    }

    //zero scenes
    void dprender_frame_thread::zeroScenes( void )
    {
        unsigned int i;

        for( i = 0; i < dprender_frame_thread_MAX_scenes; i++ )
            this->scenes[ i ] = 0;
    }

    //delete scenes
    void dprender_frame_thread::deleteScenes( void )
    {
        unsigned int i;
        dprender_scene_ref *p;

        for( i = 0; i < dprender_frame_thread_MAX_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;
            this->g.release( p );
        }

        this->zeroScenes();
    }

    //draw scenes
    void dprender_frame_thread::drawScenes( dpapi_context_writelock *ctxl, dpapi_primary_commandlist_writelock *cll )
    {
        unsigned int i;
        dprender_scene_ref *p;
        dprender_scene_writelock *pl;
        dpshared_guard g;

        for( i = 0; i < dprender_frame_thread_MAX_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;

            pl = (dprender_scene_writelock *)dpshared_guard_tryWriteLock_timeout( g, p, 30 );
            if( !pl )
                continue;

            pl->draw( ctxl, cll );
            g.release( pl );
        }
    }

    //add scene
    bool dprender_frame_thread::addScene( dprender_scene *s )
    {
        unsigned int i;
        dprender_scene_ref *p;

        for( i = 0; i < dprender_frame_thread_MAX_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( p )
                continue;
            this->scenes[ i ] = (dprender_scene_ref *)this->g.getRef( s );
            return 1;
        }

        return 0;
    }

    //remove scene
    bool dprender_frame_thread::removeScene( dprender_scene *s )
    {
        unsigned int i;
        dprender_scene_ref *p;

        for( i = 0; i < dprender_frame_thread_MAX_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;
            if( !p->isParent( s ) )
                continue;

            this->g.release( p );
            this->scenes[ i ] = 0;

            return 1;
        }

        return 0;
    }

}







