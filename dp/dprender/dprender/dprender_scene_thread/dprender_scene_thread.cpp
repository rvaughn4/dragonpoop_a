
/*

*/

#include "dprender_scene_thread.h"
#include "dprender_scene_thread_ref.h"
#include "dprender_scene_thread_readlock.h"
#include "dprender_scene_thread_writelock.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"
#include "../../dpapi/dpapi/dpapi/dpapi_factory.h"
#include "../../dpapi/dpapi/dpapi/dpapi.h"
#include "../../dpapi/dpapi/dpapi/dpapi_writelock.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist_writelock.h"
#include "../dprender/dprender.h"
#include "../../../dpdefines.h"

#if defined dprender_debug
    #include <iostream>
#endif // defined

namespace dp
{

    //ctor
    dprender_scene_thread::dprender_scene_thread( dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b ) : dptask( "Renderer scene", 3 )
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
    }

    //dtor
    dprender_scene_thread::~dprender_scene_thread( void )
    {
        this->waitForStop();
        this->unlink();
    }

    //generate readlock
    dpshared_readlock *dprender_scene_thread::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_scene_thread_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender_scene_thread::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_scene_thread_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender_scene_thread::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_scene_thread_ref( this, k, t_sync );
    }

    //override to do task execution
    bool dprender_scene_thread::onTaskRun( dptask_writelock *tl )
    {
        dpapi_commandlist_writelock *cll;
        dpapi_commandlist *pcl;
        dpapi_context_writelock *ctxl;
        std::atomic<bool> *pflag;
        dpshared_guard g;

        if( !dprender::waitForFlag( this->flag_next, 0, 10, tl ) )
            return 1;

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->ctx, 30 );
        if( !ctxl )
            return 1;

        cll = (dpapi_commandlist_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->cl_next, 30 );
        if( !cll )
            return 1;

        if( !cll->clearAndRecord( ctxl ) )
            return 1;

#if defined dprender_debug
        std::cout << "Render scene: Command buffer cleared.\r\n";
#endif // defined
        if( !this->onSceneRender( (dprender_scene_thread_writelock *)tl, ctxl, cll ) )
            return 0;
/////////

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
        std::cout << "Render scene: Command buffer compiled.\r\n";
#endif // defined

        return 1;
    }

    //override to do task startup
    bool dprender_scene_thread::onTaskStart( dptask_writelock *tl )
    {
        dpapi_context_writelock *ctxl;
        dpshared_guard g;

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->ctx, 1000 );
        if( !ctxl )
            return 0;

        if( !this->onSceneStart( (dprender_scene_thread_writelock *)tl, ctxl ) )
            return 0;

#if defined dprender_debug
        std::cout << "Render scene: Started.\r\n";
#endif // defined
        return 1;
    }

    //override to do task shutdown
    bool dprender_scene_thread::onTaskStop( dptask_writelock *tl )
    {
        dpapi_context_writelock *ctxl;
        dpshared_guard g;

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->ctx, 30 );
        if( !ctxl )
            return 0;

        if( !this->onSceneStop( (dprender_scene_thread_writelock *)tl, ctxl ) )
            return 0;

#if defined dprender_debug
        std::cout << "Render scene: Stopped.\r\n";
#endif // defined
        return 1;
    }

    //override to handle scene start
    bool dprender_scene_thread::onSceneStart( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx )
    {
        return 1;
    }

    //override to handle scene stop/cleanup
    bool dprender_scene_thread::onSceneStop( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx )
    {
        return 1;
    }

    //override to handle scene render
    bool dprender_scene_thread::onSceneRender( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        return 1;
    }

}








