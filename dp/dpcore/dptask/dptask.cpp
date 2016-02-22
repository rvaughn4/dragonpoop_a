
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#include "dptask.h"
#include "../dpshared/dpshared_guard.h"
#include "dptask_ref.h"
#include "dptask_readlock.h"
#include "dptask_writelock.h"

#include <iostream>

namespace dp
{

    //ctor
    dptask::dptask( void ) : dpshared()
    {
        this->setName( "Task" );
    }

    //dtor
    dptask::~dptask( void )
    {
    }

    //generate readlock
    dpshared_readlock *dptask::genReadLock( dpmutex_readlock *ml )
    {
        return new dptask_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dptask::genWriteLock( dpmutex_writelock *ml )
    {
        return new dptask_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dptask::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dptask_ref( this, k, t_sync );
    }

    //override to handle sync copy, be sure to call base class first!
    void dptask::onSync( dpshared_readlock *psync )
    {
        this->dpshared::onSync( psync );
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dptask::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( !this->dpshared::isSyncType( ctypename ) )
            return 0;

        return s.compare( "dptask" ) == 0;
    }

    //override to handle processing
    void dptask::onRun( dpshared_writelock *wl )
    {
        std::cout << " " << this->getTicks() << "\r\n";
    }

}




