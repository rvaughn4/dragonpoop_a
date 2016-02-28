
/*
dptaskmgr
manages threads and tasks
*/

#include "dptaskmgr.h"
#include "dptaskmgr_ref.h"
#include "dptaskmgr_readlock.h"
#include "dptaskmgr_writelock.h"

namespace dp
{

    //ctor
    dptaskmgr::dptaskmgr( unsigned int thread_cnt ) : dptask()
    {

    }

    //dtor
    dptaskmgr::~dptaskmgr( void )
    {

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
    void dptaskmgr::onTaskRun( dpthread_writelock *thd, dptask_writelock *tl )
    {

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

}





