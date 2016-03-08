
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#ifndef dptask_h
#define dptask_h

#include "dptask_defines.h"
#include "../dpshared/dpshared.h"
#include "../dpshared/dpshared_guard.h"

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dptask;
    class dptask_writelock;
    class dptask;
    class dpthread;
    class dptaskmgr;
    class dpthread_ref;
    class dptaskmgr_ref;
    class dpthread_writelock;
    class dptaskmgr_writelock;
    class dptask_ref;
    class dptask_writelock;
    class dptask_readlock;

    typedef void ( dptask::*dptask_state_method )( dptask_writelock *tl );

    class dptask : public dpshared
    {

    private:

        std::atomic<bool> bStarted, bStopped, bDoRun, bIsRun;
        dptask_state_method state;
        unsigned int ms_delay;
        char cname[ 256 ];
        dpthread_ref *runthread;
        dptaskmgr_ref *runmgr;
        dpshared_guard gt;

        //startup state
        void startstate( dptask_writelock *tl );
        //run state
        void runstate( dptask_writelock *tl );
        //shutdown state
        void stopstate( dptask_writelock *tl );
        //null state
        void nullstate( dptask_writelock *tl );
        //set owner thread
        void _setThread( dpthread_ref *t );
        //set owner taskmgr
        void _setTaskMgr( dptaskmgr_ref *t );
        //add task
        bool _addTask( dptask_ref *t, unsigned int weight );

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
        //override to do task execution
        virtual void onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual void onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual void onTaskStop( dptask_writelock *tl );
        //returns true if running
        bool isRun( void );
        //stops task
        void stop( void );
        //return ms delay
        unsigned int getDelay( void );
        //set delay
        void setDelay( unsigned int ms );
        //wait for task to finish execution
        void waitForStop( void );
        //set name
        void setName( const char *cname );
        //set thread that owns task
        void setOwnerThread( dpthread *t );
        //set thread that owns task
        void setOwnerThread( dpthread_writelock *t );
        //set thread that owns task
        void setOwnerThread( dpthread_ref *t );
        //set task manager that owns task
        void setOwnerTaskManager( dptaskmgr *t );
        //set task manager that owns task
        void setOwnerTaskManager( dptaskmgr_writelock *t );
        //set task manager that owns task
        void setOwnerTaskManager( dptaskmgr_ref *t );
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

    public:

        //ctor
        dptask( const char *cname, unsigned int ms_delay );
        //dtor
        virtual ~dptask( void );

        friend class dptask_writelock;
        friend class dptask_readlock;
    };

}

#endif



