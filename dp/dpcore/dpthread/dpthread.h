
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#ifndef dpthread_h
#define dpthread_h

#include "dpthread_defines.h"
#include "../dpshared/dpshared.h"
#include "../dpshared/dpshared_guard.h"
#include <thread>
#include <atomic>

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dpthread;
    class dptask;
    class dptask_ref;
    class dptask_readlock;
    class dptask_writelock;
    class dpthread_writelock;

    void dpthread_threadproc( dpthread *t );

    struct dpthread_dptask
    {
        dptask_ref *tsk;
        uint64_t t_last_ran, t_delay, t_next_ran, t_used;
        unsigned int weight;
    };
    #define dpthread_max_tasks 64
    struct dpthread_tasklist
    {
        dpthread_dptask tasks[ dpthread_max_tasks ];
        unsigned int cnt;
    };

    class dpthread : public dpshared
    {

    private:

        std::atomic<bool> bDoRun, bIsRun;
        std::thread *thd;
        dpthread_tasklist static_tasks, dynamic_tasks;
        dpshared_guard tg;
        unsigned int t_delay;

        //zero out tasks
        void zeroTasks( void );
        //zero out tasks
        void zeroTasks( dpthread_tasklist *tlist );
        //runs both tasklists
        bool runTasks( dpthread_writelock *thdl );
        //runs through tasklist running all tasks that need ran
        bool runTasks( dpthread_writelock *thdl, dpthread_tasklist *tlist );
        //runs task
        bool runTask( dpthread_writelock *thdl, dpthread_tasklist *tlist, dpthread_dptask *t );
        //add task to tasklist
        bool addTask( dpthread_tasklist *tlist, dptask_ref *t, unsigned int weight );
        //fetches lowest time next ran of all tasks or returns false
        bool getClosestRunTime( uint64_t *tm );
        //fetches lowest time next ran of all tasks or returns false
        bool getClosestRunTime( uint64_t *tm, dpthread_tasklist *tlist );

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to handle sync copy, be sure to call base class first!
        virtual void onSync( dpshared_readlock *psync );
        //override to test type for safe syncing, be sure to call base class first!
        virtual bool isSyncType( const char *ctypename );
        //override to handle processing
        virtual void onRun( dpshared_writelock *wl );
        //returns true if should run
        bool doRun( void );
        //returns true if running
        bool isRunning( void );
        //add a static task to task list
        bool addStaticTask( dptask *t, unsigned int weight );
        //add a static task to task list
        bool addStaticTask( dptask_ref *t, unsigned int weight );
        //add a static task to task list
        bool addStaticTask( dptask_readlock *t, unsigned int weight );
        //add a static task to task list
        bool addStaticTask( dptask_writelock *t, unsigned int weight );
        //add a dynamic task to task list
        bool addDynamicTask( dptask *t );
        //add a dynamic task to task list
        bool addDynamicTask( dptask_ref *t );
        //add a dynamic task to task list
        bool addDynamicTask( dptask_readlock *t );
        //add a dynamic task to task list
        bool addDynamicTask( dptask_writelock *t );
        //return thread delay time
        unsigned int getDelay( void );

    public:


        //ctor
        dpthread( void );
        //dtor
        virtual ~dpthread( void );

        friend class dpthread_writelock;
        friend class dpthread_readlock;
    };

}

#endif


