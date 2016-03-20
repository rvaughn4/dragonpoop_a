
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#include "dptask.h"
#include "dptask_ref.h"
#include "dptask_readlock.h"
#include "dptask_writelock.h"
#include "../dptaskmgr/dptaskmgr.h"
#include "../dptaskmgr/dptaskmgr_ref.h"
#include "../dptaskmgr/dptaskmgr_writelock.h"
#include "../dpthread/dpthread.h"
#include "../dpthread/dpthread_ref.h"
#include "../dpthread/dpthread_writelock.h"
#include "../../dpdefines.h"

#include <thread>
#include <string.h>
#include <string>
#if defined dptask_debug
    #include <iostream>
#endif

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
        this->runthread = 0;
        this->runmgr = 0;
        this->thread_no = 0;
    }

    //dtor
    dptask::~dptask( void )
    {
#if defined dptask_debug
        std::cout << "Task " << this->cname << " is stopping...(" << this->thread_no << ")\r\n";
#endif

        this->waitForStop();
        this->_setTaskMgr( 0 );
        this->_setThread( 0 );
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
#if defined dptask_debug
        std::cout << "Task " << this->cname << " .\r\n";
#endif

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
    bool dptask::onTaskRun( dptask_writelock *tl )
    {
        return 1;
    }

    //override to do task startup
    bool dptask::onTaskStart( dptask_writelock *tl )
    {
        return 1;
    }

    //override to do task shutdown
    bool dptask::onTaskStop( dptask_writelock *tl )
    {
        return 1;
    }

    //startup state
    void dptask::startstate( dptask_writelock *tl )
    {
        this->bStarted = 1;
        this->bIsRun = 1;
        if( this->onTaskStart( tl ) )
            this->state = &dptask::runstate;
        else
            this->state = &dptask::stopstate;

#if defined dptask_debug
        std::cout << "Task " << this->cname << " has started.(" << this->thread_no << ")\r\n";
#endif
    }

    //run state
    void dptask::runstate( dptask_writelock *tl )
    {
        if( !this->bDoRun || !this->onTaskRun( tl ) )
            this->state = &dptask::stopstate;

#if defined dptask_debug
        std::cout << "Task " << this->cname << " has ran.(" << this->thread_no << ")\r\n";
#endif
    }

    //shutdown state
    void dptask::stopstate( dptask_writelock *tl )
    {
        this->bStopped = 1;
        if( this->onTaskStop( tl ) )
        {
            this->state = &dptask::nullstate;
            this->bIsRun = 0;

#if defined dptask_debug
            std::cout << "Task " << this->cname << " has stopped.(" << this->thread_no << ")\r\n";
#endif
        }
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
        memset( this->cname, 0, sizeof( this->cname ) );
        s.copy( this->cname, sizeof( this->cname ) );
    }

    //set owner thread
    void dptask::_setThread( dpthread_ref *t )
    {
        if( this->runthread )
            this->gt.release( this->runthread );
        if( t )
            this->thread_no = t->thread_no;
        this->runthread = t;
    }

    //set owner taskmgr
    void dptask::_setTaskMgr( dptaskmgr_ref *t )
    {
        if( this->runmgr )
            this->gt.release( this->runmgr );
        this->runmgr = t;
    }

    //set thread that owns task
    void dptask::setOwnerThread( dpthread *t )
    {
        this->_setThread( (dpthread_ref *)this->gt.getRef( t ) );
    }

    //set thread that owns task
    void dptask::setOwnerThread( dpthread_writelock *t )
    {
        this->_setThread( (dpthread_ref *)this->gt.getRef( t ) );
    }

    //set thread that owns task
    void dptask::setOwnerThread( dpthread_ref *t )
    {
        this->_setThread( (dpthread_ref *)this->gt.getRef( t ) );
    }

    //set task manager that owns task
    void dptask::setOwnerTaskManager( dptaskmgr *t )
    {
        this->_setTaskMgr( (dptaskmgr_ref *)this->gt.getRef( t ) );
    }

    //set task manager that owns task
    void dptask::setOwnerTaskManager( dptaskmgr_writelock *t )
    {
        this->_setTaskMgr( (dptaskmgr_ref *)this->gt.getRef( t ) );
    }

    //set task manager that owns task
    void dptask::setOwnerTaskManager( dptaskmgr_ref *t )
    {
        this->_setTaskMgr( (dptaskmgr_ref *)this->gt.getRef( t ) );
    }

    //add task
    bool dptask::_addTask( dptask_ref *t, unsigned int weight )
    {
        dpshared_guard g;
        dpthread_writelock *thdl;
        dptaskmgr_writelock *mgrl;
        bool r;

        if( !t )
            return 0;
        if( !this->runmgr && !this->runthread )
            return 0;

        if( this->runmgr )
        {
            mgrl = (dptaskmgr_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->runmgr, 1000 );
            if( mgrl )
            {
                if( !weight )
                    r = mgrl->addDynamicTask( t );
                else
                    r = mgrl->addStaticTask( t, weight );
                if( r )
                {
                    this->gt.release( t );
                    return 1;
                }
            }
            g.release( mgrl );
        }

        if( this->runthread )
        {
            thdl = (dpthread_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->runthread, 1000 );
            if( thdl )
            {
                if( !weight )
                    r = thdl->addDynamicTask( t );
                else
                    r = thdl->addStaticTask( t, weight );
                if( r )
                {
                    this->gt.release( t );
                    return 1;
                }
            }
            g.release( thdl );
        }

        this->gt.release( t );
        return 0;
    }

    //add a static task to task list
    bool dptask::addStaticTask( dptask *t, unsigned int weight )
    {
        return this->_addTask( (dptask_ref *)this->gt.getRef( t ), weight );
    }

    //add a static task to task list
    bool dptask::addStaticTask( dptask_ref *t, unsigned int weight )
    {
        return this->_addTask( (dptask_ref *)this->gt.getRef( t ), weight );
    }

    //add a static task to task list
    bool dptask::addStaticTask( dptask_readlock *t, unsigned int weight )
    {
        return this->_addTask( (dptask_ref *)this->gt.getRef( t ), weight );
    }

    //add a static task to task list
    bool dptask::addStaticTask( dptask_writelock *t, unsigned int weight )
    {
        return this->_addTask( (dptask_ref *)this->gt.getRef( t ), weight );
    }

    //add a dynamic task to task list
    bool dptask::addDynamicTask( dptask *t )
    {
        return this->_addTask( (dptask_ref *)this->gt.getRef( t ), 0 );
    }

    //add a dynamic task to task list
    bool dptask::addDynamicTask( dptask_ref *t )
    {
        return this->_addTask( (dptask_ref *)this->gt.getRef( t ), 0 );
    }

    //add a dynamic task to task list
    bool dptask::addDynamicTask( dptask_readlock *t )
    {
        return this->_addTask( (dptask_ref *)this->gt.getRef( t ), 0 );
    }

    //add a dynamic task to task list
    bool dptask::addDynamicTask( dptask_writelock *t )
    {
        return this->_addTask( (dptask_ref *)this->gt.getRef( t ), 0 );
    }

    //ask task to stop and returns true if stopped
    bool dptask::stopAndDelete( dptask **t )
    {
        dptask_writelock *tskl;
        dpshared_guard g;

        if( !t )
            return 1;
        if( !( *t ) )
            return 1;

        tskl = (dptask_writelock *)dpshared_guard_tryWriteLock_timeout( g, ( *t ), 100 );
        if( !tskl )
            return 0;
        tskl->stop();
        if( tskl->isRun() )
            return 0;
        g.release( tskl );

        delete ( *t );
        *t = 0;

        return 1;
    }

}




