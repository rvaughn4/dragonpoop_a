
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

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))

namespace dp
{

    //ctor
    dptask::dptask( void ) : dpshared()
    {
        this->setName( "Task" );
        this->state = &dptask::startstate;
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
        CALL_MEMBER_FN( this, this->state )( (dptask_writelock *)wl, this->thdrun );
    }

    //called to run task
    void dptask::run( dpthread_writelock *thd, dptask_writelock *tl )
    {
        this->thdrun = thd;
        this->dpshared::run( tl );
    }

    //override to do task execution
    void dptask::onTaskRun( dpthread_writelock *thd, dptask_writelock *tl )
    {

    }

    //override to do task startup
    void dptask::onTaskStart( dpthread_writelock *thd, dptask_writelock *tl )
    {

    }

    //override to do task shutdown
    void dptask::onTaskStop( dpthread_writelock *thd, dptask_writelock *tl )
    {

    }

    //startup state
    void dptask::startstate( dptask_writelock *tl, dpthread_writelock *thd )
    {
        this->bStarted = 1;
        this->bIsRun = 1;
        this->state = &dptask::runstate;
        this->onTaskStart( thd, tl );
    }

    //run state
    void dptask::runstate( dptask_writelock *tl, dpthread_writelock *thd )
    {
        this->onTaskRun( thd, tl );
        if( !this->bDoRun )
            this->state = &dptask::stopstate;
    }

    //shutdown state
    void dptask::stopstate( dptask_writelock *tl, dpthread_writelock *thd )
    {
        this->bStopped = 1;
        this->onTaskStop( thd, tl );
        this->bIsRun = 0;
        this->state = &dptask::nullstate;
    }

    //null state
    void dptask::nullstate( dptask_writelock *tl, dpthread_writelock *thd )
    {

    }

}




