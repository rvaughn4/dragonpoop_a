
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
        return 0;
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_ref *t, unsigned int weight )
    {
        return 0;
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_readlock *t, unsigned int weight )
    {
        return 0;
    }

    //add static task
    bool dptaskmgr::addStaticTask( dptask_writelock *t, unsigned int weight )
    {
        return 0;
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask *t )
    {
        return 0;
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_ref *t )
    {
        return 0;
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_readlock *t )
    {
        return 0;
    }

    //add dynamic task
    bool dptaskmgr::addDynamicTask( dptask_writelock *t )
    {
        return 0;
    }

}





