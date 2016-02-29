
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
#include "../dptask/dptask.h"
#include "../dptask/dptask_ref.h"
#include "../dptask/dptask_readlock.h"
#include "../dptask/dptask_writelock.h"

namespace dp
{

    //ctor
    dpthread::dpthread( void ) : dpshared()
    {
        this->setName( "Thread" );
        this->bIsRun = 0;
        this->bDoRun = 1;
        this->zeroTasks();
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
        uint64_t rt, ct;

        this->t_delay = 0;
        if( this->runTasks( (dpthread_writelock *)wl ) )
            return;

        if( !this->getClosestRunTime( &rt ) )
        {
            this->t_delay = 200;
            return;
        }

        ct = this->getTicks();
        if( ct > rt )
            ct = rt;
        this->t_delay = rt - ct;
    }

    //return thread delay time
    unsigned int dpthread::getDelay( void )
    {
        return this->t_delay;
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

            tl = (dpthread_writelock *)dpshared_guard_tryWriteLock_timeout( g, tr, 100 + tms );
            if( !tl )
            {
                std::this_thread::sleep_for( std::chrono::milliseconds( tms ) );
                continue;
            }

            tl->run();
            d = tl->isRunning();
            tms = tl->getDelay();
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
        if( this->dynamic_tasks.cnt )
            return 1;
        if( this->static_tasks.cnt )
            return 1;
        return this->bIsRun;
    }

    //add a static task to task list
    bool dpthread::addStaticTask( dptask *t, unsigned int weight )
    {
        return this->addTask( &this->static_tasks, (dptask_ref *)this->tg.getRef( t ), weight );
    }

    //add a static task to task list
    bool dpthread::addStaticTask( dptask_ref *t, unsigned int weight )
    {
        return this->addTask( &this->static_tasks, (dptask_ref *)this->tg.getRef( t ), weight );
    }

    //add a static task to task list
    bool dpthread::addStaticTask( dptask_readlock *t, unsigned int weight )
    {
        return this->addTask( &this->static_tasks, (dptask_ref *)this->tg.getRef( t ), weight );
    }

    //add a static task to task list
    bool dpthread::addStaticTask( dptask_writelock *t, unsigned int weight )
    {
        return this->addTask( &this->static_tasks, (dptask_ref *)this->tg.getRef( t ), weight );
    }

    //add a dynamic task to task list
    bool dpthread::addDynamicTask( dptask *t )
    {
        return this->addTask( &this->dynamic_tasks, (dptask_ref *)this->tg.getRef( t ), 1 );
    }

    //add a dynamic task to task list
    bool dpthread::addDynamicTask( dptask_ref *t )
    {
        return this->addTask( &this->dynamic_tasks, (dptask_ref *)this->tg.getRef( t ), 1 );
    }

    //add a dynamic task to task list
    bool dpthread::addDynamicTask( dptask_readlock *t )
    {
        return this->addTask( &this->dynamic_tasks, (dptask_ref *)this->tg.getRef( t ), 1 );
    }

    //add a dynamic task to task list
    bool dpthread::addDynamicTask( dptask_writelock *t )
    {
        return this->addTask( &this->dynamic_tasks, (dptask_ref *)this->tg.getRef( t ), 1 );
    }

    //runs both tasklists
    bool dpthread::runTasks( dpthread_writelock *thdl )
    {
        bool r;

        r = this->runTasks( thdl, &this->static_tasks );
        r |= this->runTasks( thdl, &this->dynamic_tasks );

        return r;
    }

    //runs through tasklist running all tasks that need ran
    bool dpthread::runTasks( dpthread_writelock *thdl, dpthread_tasklist *tlist )
    {
        dpthread_dptask *p;
        unsigned int i;
        bool r;

        r = 0;
        for( i = 0; i < dpthread_max_tasks; i++ )
        {
            p = &tlist->tasks[ i ];
            r |= this->runTask( thdl, tlist, p );
        }

        return r;
    }

    //runs task
    bool dpthread::runTask( dpthread_writelock *thdl, dpthread_tasklist *tlist, dpthread_dptask *t )
    {
        dpshared_guard g;
        dptask_writelock *tl;
        uint64_t tstart, tdone, telasped;

        if( !t->tsk )
            return 0;

        tstart = this->getTicks();
        if( t->t_next_ran && tstart < t->t_next_ran )
            return 0;

        tl = (dptask_writelock *)dpshared_guard_tryWriteLock_timeout( g, t->tsk, 10 );
        if( !tl )
            return 0;

        tl->run();

        if( !this->bDoRun )
            tl->stop();

        if( !tl->isRun() )
        {
            g.release( tl );
            this->tg.release( t->tsk );
            t->tsk = 0;
            tlist->cnt--;
            return 1;
        }

        tdone = this->getTicks();
        t->t_delay = tl->getDelay();
        t->t_last_ran = tdone;
        telasped = tdone - tstart;
        if( telasped > t->t_delay )
            telasped = t->t_delay;
        t->t_used = telasped;
        telasped = t->t_delay - telasped;
        t->t_next_ran = tdone + telasped;

        return 1;
    }

    //add task to tasklist
    bool dpthread::addTask( dpthread_tasklist *tlist, dptask_ref *t, unsigned int weight )
    {
        dpthread_dptask *p;
        unsigned int i;

        for( i = 0; i < dpthread_max_tasks; i++ )
        {
            p = &tlist->tasks[ i ];
            if( p->tsk )
                continue;

            p->tsk = t;
            p->weight = weight;
            p->t_delay = 0;
            p->t_used = 0;
            p->t_last_ran = 0;
            p->t_next_ran = 0;
            tlist->cnt++;

            return 1;
        }

        this->tg.release( t );
        return 0;
    }

    //fetches lowest time next ran of all tasks or returns false
    bool dpthread::getClosestRunTime( uint64_t *tm )
    {
        bool r;

        r = 0;
        *tm = this->getTicks() + 1000;

        r |= this->getClosestRunTime( tm, &this->static_tasks );
        r |= this->getClosestRunTime( tm, &this->dynamic_tasks );

        return r;
    }

    //fetches lowest time next ran of all tasks or returns false
    bool dpthread::getClosestRunTime( uint64_t *tm, dpthread_tasklist *tlist )
    {
        bool r;
        dpthread_dptask *p;
        unsigned int i;

        r = 0;
        for( i = 0; i < dpthread_max_tasks; i++ )
        {
            p = &tlist->tasks[ i ];
            if( !p->tsk )
                continue;
            if( p->t_next_ran > *tm )
                continue;
            r = 1;
            *tm = p->t_next_ran;
        }

        return r;
    }

    //zero out tasks
    void dpthread::zeroTasks( void )
    {
        this->zeroTasks( &this->static_tasks );
        this->zeroTasks( &this->dynamic_tasks );
    }

    //zero out tasks
    void dpthread::zeroTasks( dpthread_tasklist *tlist )
    {
        dpthread_dptask *p;
        unsigned int i;

        for( i = 0; i < dpthread_max_tasks; i++ )
        {
            p = &tlist->tasks[ i ];
            p->tsk = 0;
        }
    }

}



