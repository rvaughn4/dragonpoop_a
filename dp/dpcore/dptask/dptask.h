
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#ifndef dptask_h
#define dptask_h

#include "dptask_defines.h"
#include "../dpshared/dpshared.h"

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dptask;
    class dpthread_writelock;
    class dptask_writelock;
    class dptask;

    typedef void ( dptask::*dptask_state_method )( dptask_writelock *tl, dpthread_writelock *thd );

    class dptask : public dpshared
    {

    private:

        dpthread_writelock *thdrun;
        std::atomic<bool> bStarted, bStopped, bDoRun, bIsRun;
        dptask_state_method state;

        //startup state
        void startstate( dptask_writelock *tl, dpthread_writelock *thd );
        //run state
        void runstate( dptask_writelock *tl, dpthread_writelock *thd );
        //shutdown state
        void stopstate( dptask_writelock *tl, dpthread_writelock *thd );
        //null state
        void nullstate( dptask_writelock *tl, dpthread_writelock *thd );

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
        //called to run task
        void run( dpthread_writelock *thd, dptask_writelock *tl );
        //override to do task execution
        virtual void onTaskRun( dpthread_writelock *thd, dptask_writelock *tl );
        //override to do task startup
        virtual void onTaskStart( dpthread_writelock *thd, dptask_writelock *tl );
        //override to do task shutdown
        virtual void onTaskStop( dpthread_writelock *thd, dptask_writelock *tl );
        //returns true if running
        bool isRun( void );
        //stops task
        void stop( void );

    public:

        //ctor
        dptask( void );
        //dtor
        virtual ~dptask( void );

        friend class dptask_writelock;
        friend class dptask_readlock;
    };

}

#endif



