
/*
dptaskmgr
manages threads and tasks
*/

#ifndef dptaskmgr_h
#define dptaskmgr_h

#include "../dptask/dptask.h"
#include "../dpshared/dpshared_guard.h"

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
    class dpthread;
    class dpthread_writelock;

    struct dptaskmgr_dptask
    {
        dptask_ref *tsk;
        unsigned int weight;
    };

    #define dptaskmgr_max_tasks 64
    struct dptaskmgr_tasklist
    {
        dptaskmgr_dptask tasks[ dptaskmgr_max_tasks ];
        unsigned int cnt;
    };

    struct dptaskmgr_dpthread
    {
        dpthread *thd;
        unsigned int weight;
        unsigned int percent_used;
    };

    #define dptaskmgr_max_threads 12
    struct dptaskmgr_threadlist
    {
        dptaskmgr_dpthread threads[ dptaskmgr_max_threads ];
        unsigned int cnt;
    };

    class dptaskmgr : public dptask
    {

    private:

        dpshared_guard tskg;
        dptaskmgr_tasklist dynamic_tasks, static_tasks;
        dptaskmgr_threadlist threads;

        //fetch and remove task from list
        dptask_ref *_nextTask( dptaskmgr_tasklist *tl, unsigned int *weight );
        //add task to list
        bool _addTask( dptaskmgr_tasklist *tl, dptask_ref *t, unsigned int weight );
        //zero tasks
        void _zeroTasks( dptaskmgr_tasklist *tl );
        //make thread
        bool _makeThread( dptaskmgr_threadlist *tl );
        //fetch thread with lowest weight
        dpthread_writelock *_fetchLowestWeightThread( dptaskmgr_threadlist *tl, dpshared_guard *g, dpthread_writelock *not_this_thread );
        //fetch thread with lowest usage
        dpthread_writelock *_fetchLowestUsageThread( dptaskmgr_threadlist *tl, dpshared_guard *g, dpthread_writelock *not_this_thread );
        //fetch thread with highest usage
        dpthread_writelock *_fetchHighestUsageThread( dptaskmgr_threadlist *tl, dpshared_guard *g, dpthread_writelock *not_this_thread );
        //process all threads
        void _runThreads( dptaskmgr_threadlist *tl );
        //delete all threads
        void _deleteThreads( dptaskmgr_threadlist *tl );
        //zero all threads
        void _zeroThreads( dptaskmgr_threadlist *tl );

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




