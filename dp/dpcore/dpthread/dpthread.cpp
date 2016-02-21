
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#include "dpthread.h"
#include "../dpshared/dpshared_guard.h"
#include "dpthread_ref.h"
#include "dpthread_readlock.h"
#include "dpthread_writelock.h"

#include <iostream>

namespace dp
{

    //ctor
    dpthread::dpthread( void ) : dpshared()
    {
        this->bIsRun = 0;
        this->bDoRun = 1;
        this->thd = new std::thread( dpthread_threadproc, this );
        while( !this->bIsRun )
            std::this_thread::sleep_for( std::chrono::milliseconds( 0 ) );
    }

    //dtor
    dpthread::~dpthread( void )
    {
        this->bDoRun = 0;
        while( this->bIsRun )
            std::this_thread::sleep_for( std::chrono::milliseconds( 0 ) );
        if( this->thd->joinable() )
            this->thd->join();
        delete this->thd;
    }

    //generate readlock
    dpshared_readlock *dpthread::genReadLock( dpmutex_readlock *ml )
    {
        return new dpthread_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpthread::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpthread_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpthread::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpthread_ref( this, k, t_sync );
    }

    //override to handle sync copy, be sure to call base class first!
    void dpthread::onSync( dpshared_readlock *psync )
    {
        this->dpshared::onSync( psync );
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dpthread::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( !this->dpshared::isSyncType( ctypename ) )
            return 0;

        return s.compare( "dpthread" ) == 0;
    }

    //override to handle processing
    void dpthread::onRun( dpshared_writelock *wl )
    {

        this->bIsRun = this->bDoRun & 1;

        std::cout << ".";

    }

    void dpthread_threadproc( dpthread *t )
    {
        dpthread_ref *tr;
        dpthread_writelock *tl;
        dpshared_guard g;
        bool d;
        unsigned int tms = 30;

        tr = (dpthread_ref *)g.getRef( t );
        if( !tr )
            return;

        d = 1;
        while( d )
        {
            if( !tr->isLinked() )
                return;

            tl = (dpthread_writelock *)dpshared_guard_tryWriteLock_timeout( g, tr, 10 );
            if( !tl )
            {
                std::this_thread::sleep_for( std::chrono::milliseconds( tms ) );
                continue;
            }

            tl->run();
            d = tl->isRunning();
            g.release( tl );

            std::this_thread::sleep_for( std::chrono::milliseconds( tms ) );
        }
    }

    //returns true if should run
    bool dpthread::doRun( void )
    {
        return this->bDoRun;
    }

    //returns true if running
    bool dpthread::isRunning( void )
    {
        return this->bIsRun;
    }

}



