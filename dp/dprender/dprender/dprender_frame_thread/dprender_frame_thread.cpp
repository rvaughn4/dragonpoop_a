
/*

*/

#include "dprender_frame_thread.h"
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
    }

    //dtor
    dprender_frame_thread::~dprender_frame_thread( void )
    {

    }

    //override to do task execution
    bool dprender_frame_thread::onTaskRun( dptask_writelock *tl )
    {
        dpapi_primary_commandlist_writelock *cll;
        dpapi_primary_commandlist *pcl;
        dpapi_context_writelock *ctxl;
        std::atomic<bool> *pflag;
        dpshared_guard g;

        if( !dprender::waitForFlag( this->flag_next, 0, 10, tl ) )
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
#if defined dprender_debug
        std::cout << "Render Frame: Stopped.\r\n";
#endif // defined
        return 1;
    }

    //add scene
    bool dprender_frame_thread::addScene( dprender_scene *s, dpapi_writelock *apil, dprender_writelock *rl, dprender_frame_thread_writelock *tl )
    {
        dpshared_guard g;
        dprender_scene_writelock *sl;
        bool r;

        sl = (dprender_scene_writelock *)dpshared_guard_tryWriteLock_timeout( g, s, 1000 );
        if( !sl )
            return 0;

        if( !sl->attach( apil, rl, tl ) )
            return 0;

        g.release( sl );
        return this->addDynamicTask( s );
    }

}







