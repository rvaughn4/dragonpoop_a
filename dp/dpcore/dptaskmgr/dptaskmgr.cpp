
/*
dptaskmgr
manages threads and tasks
*/

#include "dptaskmgr.h"
#include "dptaskmgr_ref.h"
#include "dptaskmgr_readlock.h"
#include "dptaskmgr_writelock.h"
#include "../dpthread/dpthread.h"
#include "../dpthread/dpthread_writelock.h"
#include "../dpthread/dpthread_readlock.h"

#include <iostream>

namespace dp
{

    //ctor
    dptaskmgr::dptaskmgr( unsigned int thread_cnt ) : dptask( "Task Manager", 1000 )
    {
        dpthread_writelock *tl;
        dpshared_guard g;

        this->_zeroTasks( &this->static_tasks );
        this->_zeroTasks( &this->dynamic_tasks );
        this->_zeroThreads( &this->threads );

        if( !thread_cnt )
            thread_cnt = 4;

        while( thread_cnt )
        {
            this->_makeThread( &this->threads );
            thread_cnt--;
        }

        this->wtsk = new dpwindow_task( new dpwindow_factory() );

        tl = this->_fetchLowestWeightThread( &this->threads, &g, 0 );
        if( tl )
            tl->addStaticTask( this, 1 );
       // if( tl )
         //   tl->addStaticTask( this->wtsk, 1 );

        g.release( tl );
    }

    //dtor
    dptaskmgr::~dptaskmgr( void )
    {
        this->_deleteTasks( &this->static_tasks );
        this->_deleteTasks( &this->dynamic_tasks );
        this->_deleteThreads( &this->threads );
        this->waitForStop();
        delete this->wtsk;
    }

    //generate readlock
    dpshared_readlock *dptaskmgr::genReadLock( dpmutex_readlock *ml )
    {
        return new dptaskmgr_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dptaskmgr::genWriteLock( dpmutex_writelock *ml )
    {
        return new dptaskmgr_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dptaskmgr::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dptaskmgr_ref( this, k, t_sync );
    }

    //override to do task execution
    void dptaskmgr::onTaskRun( dpthread_writelock *thd, dptask_writelock *ptl )
    {
        dptask_ref *tr;
        unsigned int w, tries;
        dpthread_writelock *tl;
        dpshared_guard g;

        std::cout << " " << this->getTicks() << " \r\n";

        tr = this->_nextTask( &this->static_tasks, &w );
        if( tr )
        {
            tl = this->_fetchLowestWeightThread( &this->threads, &g, 0 );
/*            if( !tl || !tl->addStaticTask( tr, w ) )
                this->_addTask( &this->static_tasks, tr, w );
            else
                this->tskg.release( tr );
  */      }

//        this->_runThreads( &this->threads );
    }

    //override to do task startup
    void dptaskmgr::onTaskStart( dpthread_writelock *thd, dptask_writelock *tl )
    {

    }

    //override to do task shutdown
    void dptaskmgr::onTaskStop( dpthread_writelock *thd, dptask_writelock *tl )
    {

    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask *t, unsigned int weight )
    {
        return this->_addTask( &this->static_tasks, (dptask_ref *)this->tskg.getRef( t ), weight );
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_ref *t, unsigned int weight )
    {
        return this->_addTask( &this->static_tasks, (dptask_ref *)this->tskg.getRef( t ), weight );
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_readlock *t, unsigned int weight )
    {
        return this->_addTask( &this->static_tasks, (dptask_ref *)this->tskg.getRef( t ), weight );
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_writelock *t, unsigned int weight )
    {
        return this->_addTask( &this->static_tasks, (dptask_ref *)this->tskg.getRef( t ), weight );
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask *t )
    {
        return this->_addTask( &this->dynamic_tasks, (dptask_ref *)this->tskg.getRef( t ), 1 );
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_ref *t )
    {
        return this->_addTask( &this->dynamic_tasks, (dptask_ref *)this->tskg.getRef( t ), 1 );
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_readlock *t )
    {
        return this->_addTask( &this->dynamic_tasks, (dptask_ref *)this->tskg.getRef( t ), 1 );
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_writelock *t )
    {
        return this->_addTask( &this->dynamic_tasks, (dptask_ref *)this->tskg.getRef( t ), 1 );
    }

    //fetch and remove task from list
    dptask_ref *dptaskmgr::_nextTask( dptaskmgr_tasklist *tl, unsigned int *weight )
    {
        unsigned int i;
        dptaskmgr_dptask *p;
        dptask_ref *r;

        for( i = 0; i < dptaskmgr_max_tasks; i++ )
        {
            p = &tl->tasks[ i ];
            if( !p->tsk )
                continue;
            r = p->tsk;
            if( weight )
                *weight = p->weight;
            p->tsk = 0;
            return r;
        }

        return 0;
    }

    //add task to list
    bool dptaskmgr::_addTask( dptaskmgr_tasklist *tl, dptask_ref *t, unsigned int weight )
    {
        unsigned int i;
        dptaskmgr_dptask *p;

        for( i = 0; i < dptaskmgr_max_tasks; i++ )
        {
            p = &tl->tasks[ i ];
            if( p->tsk )
                continue;
            p->tsk = t;
            p->weight = weight;
            return 1;
        }

        this->tskg.release( t );
        return 0;
    }

    //zero tasks
    void dptaskmgr::_zeroTasks( dptaskmgr_tasklist *tl )
    {
        unsigned int i;
        dptaskmgr_dptask *p;

        for( i = 0; i < dptaskmgr_max_tasks; i++ )
        {
            p = &tl->tasks[ i ];
            p->tsk = 0;
            p->weight = 0;
        }
    }

    //delete tasks
    void dptaskmgr::_deleteTasks( dptaskmgr_tasklist *tl )
    {
        unsigned int i;
        dptaskmgr_dptask *p;
        dptask_writelock *l;
        dpshared_guard g;

        for( i = 0; i < dptaskmgr_max_tasks; i++ )
        {
            p = &tl->tasks[ i ];
            if( !p->tsk )
                continue;

            l = (dptask_writelock *)dpshared_guard_tryWriteLock_timeout( g, p->tsk, 1000 );
            if( l )
            {
                l->stop();
                g.release( l );
            }

            this->tskg.release( p->tsk );
        }

        this->_zeroTasks( tl );
    }

    //make thread
    bool dptaskmgr::_makeThread( dptaskmgr_threadlist *tl )
    {
        unsigned int i;
        dptaskmgr_dpthread *p;

        for( i = 0; i < dptaskmgr_max_threads; i++ )
        {
            p = &tl->threads[ i ];
            if( p->thd )
                continue;
            p->weight = 0;
            p->percent_used = 0;
            p->thd = new dpthread();
            tl->cnt++;
            return 1;
        }

        return 0;
    }

    //fetch thread with lowest weight
    dpthread_writelock *dptaskmgr::_fetchLowestWeightThread( dptaskmgr_threadlist *tl, dpshared_guard *g, dpthread_writelock *not_this_thread )
    {
        unsigned int i, lw;
        dptaskmgr_dpthread *p, *r;
        dpthread_writelock *rl;

        r = 0;
        lw = dptaskmgr_max_threads * 99999;
        for( i = 0; i < dptaskmgr_max_threads; i++ )
        {
            p = &tl->threads[ i ];
            if( !p->thd )
                continue;
                r = p;
        //rl = (dpthread_writelock *)dpshared_guard_tryWriteLock_timeout( (*g), r->thd, 1000 );
        rl = (dpthread_writelock *)dpshared_guard_writeLock_block( (*g), r->thd );
        return rl;
/*

            if( p->weight > lw )
                continue;
            lw = p->weight;
            r = p;
*/        }

        if( !r )
            return 0;

        rl = (dpthread_writelock *)dpshared_guard_tryWriteLock_timeout( (*g), r->thd, 100 );
        return rl;
    }

    //fetch thread with lowest usage
    dpthread_writelock *dptaskmgr::_fetchLowestUsageThread( dptaskmgr_threadlist *tl, dpshared_guard *g, dpthread_writelock *not_this_thread )
    {
        unsigned int i, lw;
        dptaskmgr_dpthread *p, *r;
        dpthread_writelock *rl;

        r = 0;
        lw = 101;
        for( i = 0; i < dptaskmgr_max_threads; i++ )
        {
            p = &tl->threads[ i ];
            if( !p->thd )
                continue;
            if( p->percent_used < lw )
                continue;
            lw = p->percent_used;
            r = p;
        }

        if( !r )
            return 0;

        rl = (dpthread_writelock *)dpshared_guard_tryWriteLock_timeout( (*g), r->thd, 100 );
        return rl;
    }

    //fetch thread with highest usage
    dpthread_writelock *dptaskmgr::_fetchHighestUsageThread( dptaskmgr_threadlist *tl, dpshared_guard *g, dpthread_writelock *not_this_thread )
    {
        unsigned int i, lw;
        dptaskmgr_dpthread *p, *r;
        dpthread_writelock *rl;

        r = 0;
        lw = 0;
        for( i = 0; i < dptaskmgr_max_threads; i++ )
        {
            p = &tl->threads[ i ];
            if( !p->thd )
                continue;
            if( p->percent_used >= lw )
                continue;
            lw = p->percent_used;
            r = p;
        }

        if( !r )
            return 0;

        rl = (dpthread_writelock *)dpshared_guard_tryWriteLock_timeout( (*g), r->thd, 100 );
        return rl;
    }

    //process all threads
    void dptaskmgr::_runThreads( dptaskmgr_threadlist *tl )
    {
        unsigned int i;
        dptaskmgr_dpthread *p;
        dpthread_readlock *thdl;
        dpshared_guard g;

        for( i = 0; i < dptaskmgr_max_threads; i++ )
        {
            p = &tl->threads[ i ];
            if( !p->thd )
                continue;
            thdl = (dpthread_readlock *)dpshared_guard_tryReadLock_timeout( g, p->thd, 30 );
            if( !thdl )
                continue;
            p->percent_used = 50;//thdl->getPercentUsed();
        }
    }

    //delete all threads
    void dptaskmgr::_deleteThreads( dptaskmgr_threadlist *tl )
    {
        unsigned int i;
        dptaskmgr_dpthread *p;

        for( i = 0; i < dptaskmgr_max_threads; i++ )
        {
            p = &tl->threads[ i ];
            if( !p->thd )
                continue;
            delete p->thd;
        }

        this->_zeroThreads( tl );
    }

    //zero all threads
    void dptaskmgr::_zeroThreads( dptaskmgr_threadlist *tl )
    {
        unsigned int i;
        dptaskmgr_dpthread *p;

        for( i = 0; i < dptaskmgr_max_threads; i++ )
        {
            p = &tl->threads[ i ];
            p->thd = 0;
            p->percent_used = 0;
            p->weight = 0;
        }
    }

}





