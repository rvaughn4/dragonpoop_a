
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
#include "../dprender_frame_thread/dprender_frame_thread.h"

namespace dp
{

    //ctor
    dprender::dprender( dpapi_factory *wf ) : dptask( "Renderer Main", 30 )
    {
        this->apifactory = wf;
        this->api = 0;
        this->main_ctx = this->frame_ctx = 0;
        this->cl_a = this->cl_b = 0;
        this->flag_a = this->flag_b = 0;
        this->frametask = 0;
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
    void dprender::onTaskRun( dptask_writelock *tl )
    {
        dpapi_primary_commandlist_writelock *cll;
        dpapi_primary_commandlist *pcl;
        dpapi_context_writelock *ctxl;
        std::atomic<bool> *pflag;
        dpshared_guard g;

        if( !( *this->flag_next ) )
            return;

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->main_ctx, 30 );
        if( !ctxl )
            return;

        cll = (dpapi_primary_commandlist_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->cl_next, 30 );
        if( !cll )
            return;

        cll->execute( ctxl );
        ( *this->flag_next ) = 0;

        pcl = this->cl_next;
        pflag = this->flag_next;

        this->cl_next = this->cl_prev;
        this->flag_next = this->flag_prev;

        this->cl_prev = pcl;
        this->flag_prev = pflag;
    }

    //override to do task startup
    void dprender::onTaskStart( dptask_writelock *tl )
    {
        dpshared_guard g;
        dpapi_writelock *apil;
        dpapi_context_writelock *ctxl;

        if( !this->apifactory )
        {
            this->stop();
            return;
        }

        this->api = this->apifactory->makeApi();
        if( !this->api )
        {
            this->stop();
            return;
        }

        apil = (dpapi_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->api, 1000 );
        if( !apil )
        {
            this->stop();
            return;
        }

        this->main_ctx = apil->makeContext();
        this->frame_ctx = apil->makeContext();

        g.release( apil );
        if( !this->main_ctx || !this->frame_ctx )
        {
            this->stop();
            return;
        }

        ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->main_ctx, 1000 );
        if( !ctxl )
        {
            this->stop();
            return;
        }

        this->cl_a = ctxl->makePrimaryCommandList();
        this->cl_b = ctxl->makePrimaryCommandList();

        g.release( ctxl );
        if( !this->cl_a || !this->cl_b )
        {
            this->stop();
            return;
        }

        this->flag_a = this->flag_b = 0;
        this->cl_next = this->cl_a;
        this->flag_next = &this->flag_a;
        this->cl_prev = this->cl_b;
        this->flag_prev = &this->flag_b;

        this->frametask = new dprender_frame_thread( this->frame_ctx, this->cl_a, this->cl_b, &this->flag_a, &this->flag_b );
        if( !this->frametask )
        {
            this->stop();
            return;
        }

        if( !this->addStaticTask( this->frametask, 1 ) )
        {
            this->stop();
            return;
        }
    }

    //override to do task shutdown
    void dprender::onTaskStop( dptask_writelock *tl )
    {
        if( this->frametask )
            delete this->frametask;
        this->frametask = 0;

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
    }

}







