
/*
dptaskmgr
manages threads and tasks
*/

#ifndef dptaskmgr_h
#define dptaskmgr_h

#include "../dptask/dptask.h"

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dptask;
    class dpthread_writelock;
    class dptask;
    class dptask_ref;
    class dptask_readlock;
    class dptask_writelock;

    class dptaskmgr : public dptask
    {

    private:

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to do task execution
        virtual void onTaskRun( dpthread_writelock *thd, dptask_writelock *tl );
        //override to do task startup
        virtual void onTaskStart( dpthread_writelock *thd, dptask_writelock *tl );
        //override to do task shutdown
        virtual void onTaskStop( dpthread_writelock *thd, dptask_writelock *tl );
        //add static task
        bool addStaticTask( dptask *t, unsigned int weight );
        //add static task
        bool addStaticTask( dptask_ref *t, unsigned int weight );
        //add static task
        bool addStaticTask( dptask_readlock *t, unsigned int weight );
        //add static task
        bool addStaticTask( dptask_writelock *t, unsigned int weight );
        //add dynamic task
        bool addDynamicTask( dptask *t );
        //add dynamic task
        bool addDynamicTask( dptask_ref *t );
        //add dynamic task
        bool addDynamicTask( dptask_readlock *t );
        //add dynamic task
        bool addDynamicTask( dptask_writelock *t );

    public:

        //ctor
        dptaskmgr( unsigned int thread_cnt );
        //dtor
        virtual ~dptaskmgr( void );

        friend class dptaskmgr_writelock;
        friend class dptaskmgr_readlock;
    };

}

#endif




