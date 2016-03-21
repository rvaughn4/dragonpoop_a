
/*

*/

#include "dprender_gui_thread.h"
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

#include "../../dpapi/dpapi/dpapi_indexbuffer/dpapi_indexbuffer.h"
#include "../../dpapi/dpapi/dpapi_vertexbuffer/dpapi_vertexbuffer.h"
#include "../../dpapi/dpapi/dpapi_bundle/dpapi_bundle.h"
#include "../../dpvertex/dpindexbuffer.h"
#include "../../dpvertex/dpvertexbuffer.h"

#if defined dprender_debug
#include <iostream>
#endif // defined

namespace dp
{

    //ctor
    dprender_gui_thread::dprender_gui_thread( dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b ) : dptask( "Renderer gui", 3 )
    {
        dpvertexbuffer vb;
        dpindexbuffer ib;
        dpapi_context_writelock *ctxl;
        dpshared_guard g;

        this->ctx = ctx;
        this->cl_a = cl_a;
        this->cl_b = cl_b;
        this->flag_a = flag_a;
        this->flag_b = flag_b;
        this->cl_next = this->cl_a;
        this->cl_prev = this->cl_b;
        this->flag_next = this->flag_a;
        this->flag_prev = this->flag_b;

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->ctx, 1000 );

        dpindex i;

        i.i = 0;
        ib.write( &i );
        i.i = 1;
        ib.write( &i );
        i.i = 2;
        ib.write( &i );

        dpvertex v;

        v.vert.x = 0;
        v.vert.y = 0;
        v.vert.z = 0;
        vb.write( &v );
        v.vert.x = 0;
        v.vert.y = -1;
        v.vert.z = 0;
        vb.write( &v );
        v.vert.x = 1;
        v.vert.y = -1;
        v.vert.z = 1;
        vb.write( &v );

        this->ib = ctxl->makeIndexBuffer( &ib );
        this->vb = ctxl->makeVertexBuffer( &vb );
        this->bdle = ctxl->makeBundle( this->vb, this->ib, 0, 0, 0 );
    }

    //dtor
    dprender_gui_thread::~dprender_gui_thread( void )
    {
        this->waitForStop();
        this->unlink();

        delete this->bdle;
        delete this->vb;
        delete this->ib;
    }

    //override to do task execution
    bool dprender_gui_thread::onTaskRun( dptask_writelock *tl )
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
        std::cout << "Render gui: Command buffer cleared.\r\n";
#endif // defined


        cll->addBundle( ctxl, this->bdle );
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
        std::cout << "Render gui: Command buffer compiled.\r\n";
#endif // defined

        return 1;
    }

    //override to do task startup
    bool dprender_gui_thread::onTaskStart( dptask_writelock *tl )
    {
#if defined dprender_debug
        std::cout << "Render gui: Started.\r\n";
#endif // defined
        return 1;
    }

    //override to do task shutdown
    bool dprender_gui_thread::onTaskStop( dptask_writelock *tl )
    {
#if defined dprender_debug
        std::cout << "Render gui: Stopped.\r\n";
#endif // defined
        return 1;
    }

}








