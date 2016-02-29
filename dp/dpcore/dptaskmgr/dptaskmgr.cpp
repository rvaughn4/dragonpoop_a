
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
#include <list>

namespace dp
{

    //ctor
    dptaskmgr::dptaskmgr( unsigned int thread_cnt ) : dptask( "Task Manager", 1000 )
    {
        this->_zeroThreads( &this->threads );

        if( !thread_cnt )
            thread_cnt = 4;

        while( thread_cnt )
        {
            this->_makeThread( &this->threads );
            thread_cnt--;
        }

       // this->wtsk = new dpwindow_task( new dpwindow_factory() );

        this->addStaticTask( this, 1 );
        //this->addStaticTask( this->wtsk, 1 );
    }

    //dtor
    dptaskmgr::~dptaskmgr( void )
    {
        this->_deleteThreads( &this->threads );
        this->waitForStop();
       // delete this->wtsk;
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

        std::cout << " " << this->getTicks() << " \r\n";


        this->_runThreads( &this->threads );
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
        return this->_addTask( &this->threads, t, weight );
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_ref *t, unsigned int weight )
    {
        return 0;//this->_addTask( &this->threads, (dptask_ref *)this->tskg.getRef( t ), weight );
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_readlock *t, unsigned int weight )
    {
        return 0;//this->_addTask( &this->threads, (dptask_ref *)this->tskg.getRef( t ), weight );
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_writelock *t, unsigned int weight )
    {
        return 0;//this->_addTask( &this->threads, (dptask_ref *)this->tskg.getRef( t ), weight );
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask *t )
    {
        return this->_addTask( &this->threads, t, 0 );
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_ref *t )
    {
        return 0;//this->_addTask( &this->threads, (dptask_ref *)this->tskg.getRef( t ), 0 );
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_readlock *t )
    {
        return 0;//this->_addTask( &this->threads, (dptask_ref *)this->tskg.getRef( t ), 0 );
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_writelock *t )
    {
        return 0;//this->_addTask( &this->threads, (dptask_ref *)this->tskg.getRef( t ), 0 );
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

    //add task to thread with least static tasks
    bool dptaskmgr::_addTask( dptaskmgr_threadlist *tl, dptask *t, unsigned int weight )
    {
        unsigned int i, lw;
        dptaskmgr_dpthread *p;
        std::list<dpthread *> lt;
        std::list<dpthread *>::iterator it;
        dpthread *pt;
        dpthread_writelock *ptl;
        dpshared_guard g;
        bool r;

        lw = dptaskmgr_max_threads * 900;
        for( i = 0; i < dptaskmgr_max_threads; i++ )
        {
            p = &tl->threads[ i ];
            if( !p->thd )
                continue;
            if( p->weight < lw )
            {
                lw = p->weight;
                lt.push_front( p->thd );
            }
            else
                lt.push_back( p->thd );
        }

        r = 0;
        for( it = lt.begin(); it != lt.end() && !r; ++it )
        {
            pt = *it;

            ptl = (dpthread_writelock *)dpshared_guard_tryWriteLock_timeout( g, pt, 30 );
            if( !ptl )
                continue;

            if( !weight )
                r = ptl->addDynamicTask( t );
            else
                r = ptl->addStaticTask( t, weight );
        }

        return r;
    }


}





