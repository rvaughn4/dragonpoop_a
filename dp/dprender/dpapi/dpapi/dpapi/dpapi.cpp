
/*

*/

#include "dpapi.h"
#include "dpapi_ref.h"
#include "dpapi_readlock.h"
#include "dpapi_writelock.h"
#include "../../../dpwindow/dpwindow/dpwindow_factory.h"
#include "../../../dpwindow/dpwindow/dpwindow.h"
#include "../../../dpwindow/dpwindow/dpwindow_writelock.h"
#include "../../../../dpcore/dpshared/dpshared_guard.h"
#include "../dpapi_context/dpapi_context.h"

namespace dp
{

    //ctor
    dpapi::dpapi( dpwindow_factory *wf )
    {
        this->bIsStarted = 0;
        this->bIsOpen = 0;
        this->wf = wf;
        this->w = wf->makeWindow();
    }

    //dtor
    dpapi::~dpapi( void )
    {
        this->unlink();
        delete this->w;
        delete this->wf;
    }

    //generate readlock
    dpshared_readlock *dpapi::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_ref( this, k, t_sync );
    }

    //override to handle sync copy, be sure to call base class first!
    void dpapi::onSync( dpshared_readlock *psync )
    {
        this->dpshared::onSync( psync );
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dpapi::isSyncType( const char *ctypename )
    {
        if( this->dpshared::isSyncType( ctypename ) )
            return 1;

        return 0;
    }

    //override to handle processing
    void dpapi::onRun( dpshared_writelock *wl )
    {
        dpwindow_writelock *wndl;
        dpshared_guard g;
        bool b;

        this->dpshared::onRun( wl );

        wndl = (dpwindow_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->w, 3 );

        if( wndl )
        {
            wndl->run();
            b = wndl->isOpen();

            if( !this->bIsStarted && b )
                this->bIsStarted = this->bIsOpen = this->initApi( wndl, (dpapi_writelock *)wl );

            this->bIsOpen &= b;

            g.release( wndl );
        }

        if( this->bIsOpen )
            this->runApi( (dpapi_writelock *)wl );
    }

    //returns true if open
    bool dpapi::isOpen( void )
    {
        return this->bIsOpen;
    }

    //override to init api
    bool dpapi::initApi( dpwindow_writelock *wl, dpapi_writelock *al )
    {
        return 1;
    }

    //override to run api
    void dpapi::runApi( dpapi_writelock *al )
    {
        this->onFrameStart();
        this->onFrameEnd();
    }

    //override to generate rendering context
    dpapi_context *dpapi::makeContext( dpapi_writelock *al )
    {
        return new dpapi_context( al );
    }

    //override to handle end of frame
    void dpapi::onFrameEnd( void )
    {

    }

    //override to handle start of frame
    void dpapi::onFrameStart( void )
    {

    }

}






