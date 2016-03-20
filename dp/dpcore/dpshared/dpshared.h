
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#ifndef dpshared_h
#define dpshared_h

#include "dpshareddefines.h"
#include "dpshared_ref_kernel.h"
#include <atomic>
#include <memory>

namespace dp
{

    class dpshared_ref;
    class dpshared_readlock;
    class dpshared_writelock;
    class dpmutex;
    class dpmutex_readlock;
    class dpmutex_writelock;

    class dpshared
    {

    private:

        dpmutex *m;
        dpshared_ref *rsync;
        std::shared_ptr< std::atomic<uint64_t> > t_sync;
        std::shared_ptr<dpshared_ref_kernel> k;
#ifdef dpshared_debug
        const char *cname;

        const char *cfile_macro;
        unsigned int line_macro;
        const char *cfunc_macro;
#endif

    protected:

        //set object name for debug output
        void setName( const char *cname );
        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //set shared object to sync by
        void setSync( dpshared *psync );
        //set shared object to sync by
        void setSync( dpshared_ref *psync );
        //set shared object to sync by
        void setSync( dpshared_readlock *psync );
        //set shared object to sync by
        void setSync( dpshared_writelock *psync );
        //sync with shared object stored inside if internal time mismatched
        void sync( void );
        //update internal time to cause objects to sync
        void update( void );
        //override to handle sync copy, be sure to call base class first!
        virtual void onSync( dpshared_readlock *psync );
        //override to test type for safe syncing, be sure to call base class first!
        virtual bool isSyncType( const char *ctypename );
        //called to run
        void run( dpshared_writelock *wl );
        //override to handle processing
        virtual void onRun( dpshared_writelock *wl );
        //attempt readlock
        dpshared_readlock *_usemacro_tryReadLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    );
        //attempt writelock
        dpshared_writelock *_usemacro_tryWriteLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    );
        //attempt readlock until timeout in milliseconds
        dpshared_readlock *_usemacro_tryReadLock( unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt writelock until timeout in milliseconds
        dpshared_writelock *_usemacro_tryWriteLock( unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt readlock forever
        dpshared_readlock *_usemacro_readLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    );
        //attempt writelock forever
        dpshared_writelock *_usemacro_writeLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    );
        //get reference
        dpshared_ref *getRef( void );
        //returns current epoch time in seconds
        uint64_t getEpoch( void );
        //returns tickcount in ms
        uint64_t getTicks( void );
        //unlink
        void unlink( void );

    public:


        //ctor
        dpshared( void );
        //dtor
        virtual ~dpshared( void );


        friend class dpshared_writelock;
        friend class dpshared_readlock;
        friend class dpshared_ref;
        friend class dpshared_guard;
    };

}

#endif

