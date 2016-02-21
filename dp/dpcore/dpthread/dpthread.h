
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#ifndef dpthread_h
#define dpthread_h

#include "dpthread_defines.h"
#include "../dpshared/dpshared.h"
#include <thread>
#include <atomic>

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dpthread;

    void dpthread_threadproc( dpthread *t );

    class dpthread : public dpshared
    {

    private:

        std::atomic<bool> bDoRun, bIsRun;
        std::thread *thd;

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

    public:


        //ctor
        dpthread( void );
        //dtor
        virtual ~dpthread( void );

        friend class dpthread_writelock;
    };

}

#endif


