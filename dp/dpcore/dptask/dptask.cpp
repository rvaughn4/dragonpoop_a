
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

#include <thread>
#include <string>
#include <iostream>

namespace dp
{

    //ctor
    dptask::dptask( const char *cname, unsigned int ms_delay ) : dpshared()
    {
        this->setName( cname );
        this->state = &dptask::startstate;
        this->bDoRun = 1;
        this->bIsRun = 0;
        this->ms_delay = ms_delay;
    }

    //dtor
    dptask::~dptask( void )
    {
        this->waitForStop();
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
        std::cout << "Task " << this->cname << " .\r\n";


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
        ( ( this )->*( this->state ) )( (dptask_writelock *)wl );
    }

    //override to do task execution
    void dptask::onTaskRun( dptask_writelock *tl )
    {

    }

    //override to do task startup
    void dptask::onTaskStart( dptask_writelock *tl )
    {

    }

    //override to do task shutdown
    void dptask::onTaskStop( dptask_writelock *tl )
    {

    }

    //startup state
    void dptask::startstate( dptask_writelock *tl )
    {
        this->bStarted = 1;
        this->bIsRun = 1;
        this->state = &dptask::runstate;
        this->onTaskStart( tl );

        std::cout << "Task " << this->cname << " has started.\r\n";
    }

    //run state
    void dptask::runstate( dptask_writelock *tl )
    {
        this->onTaskRun( tl );
        if( !this->bDoRun )
            this->state = &dptask::stopstate;
        std::cout << "Task " << this->cname << " has ran.\r\n";
    }

    //shutdown state
    void dptask::stopstate( dptask_writelock *tl )
    {
        this->bStopped = 1;
        this->onTaskStop( tl );
        this->state = &dptask::nullstate;
        std::cout << "Task " << this->cname << " has stopped.\r\n";
        this->bIsRun = 0;
    }

    //null state
    void dptask::nullstate( dptask_writelock *tl )
    {

    }

    //returns true if running
    bool dptask::isRun( void )
    {
        return this->bIsRun;
    }

    //stops task
    void dptask::stop( void )
    {
        this->bDoRun = 0;
    }

    //return ms delay
    unsigned int dptask::getDelay( void )
    {
        return this->ms_delay;
    }

    //set delay
    void dptask::setDelay( unsigned int ms )
    {
        this->ms_delay = ms;
    }

    //wait for task to finish execution
    void dptask::waitForStop( void )
    {
        bool b;

        this->stop();

        b = this->bIsRun;
        while( b )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds( 1 ) );
            b = this->bIsRun;
        }
    }

    //set name
    void dptask::setName( const char *cname )
    {
        std::string s( cname );

        this->dpshared::setName( cname );
        s.copy( this->cname, sizeof( this->cname ) );
    }

}




