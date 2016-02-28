
/*
mutex implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the mutex
*/

#ifndef dpmutex_h
#define dpmutex_h

#include "dpmutexdefines.h"
#include <atomic>
#include <thread>

namespace dp
{

    class dpmutexmaster;
    class dpmutex_readlock;
    class dpmutex_writelock;
    class dpspinlock;

    class dpmutex
    {

    private:

        dpmutexmaster *mm;
        dpspinlock *slk;
        std::atomic<int> rlock_ctr, wlock_ctr;
        std::thread::id wlock_tid;

    protected:

        //unlock
        void unlock(
                    dpmutex_readlock *l
#ifdef dpmutex_debug
                    ,
                    const char *cfile_macro,
                    unsigned int line_macro,
                    const char *cfunc_macro
#endif
                    );
        //unlock
        void unlock(
                    dpmutex_writelock *l
#ifdef dpmutex_debug
                    ,
                    const char *cfile_macro,
                    unsigned int line_macro,
                    const char *cfunc_macro
#endif
                    );

    public:


        //ctor
        dpmutex( void );
        //ctor
        dpmutex( dpmutexmaster *mm );
        //dtor
        virtual ~dpmutex( void );
        //attempt readlock
        dpmutex_readlock *_usemacro_tryReadLock(
#ifdef dpmutex_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    );
        //attempt writelock
        dpmutex_writelock *_usemacro_tryWriteLock(
#ifdef dpmutex_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    );
        //attempt readlock until timeout in milliseconds
        dpmutex_readlock *_usemacro_tryReadLock( unsigned int timeout_ms
#ifdef dpmutex_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt writelock until timeout in milliseconds
        dpmutex_writelock *_usemacro_tryWriteLock( unsigned int timeout_ms
#ifdef dpmutex_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt readlock forever
        dpmutex_readlock *_usemacro_readLock(
#ifdef dpmutex_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    );
        //attempt writelock forever
        dpmutex_writelock *_usemacro_writeLock(
#ifdef dpmutex_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    );

        //returns current epoch time in seconds
        uint64_t getEpoch( void );
        //returns tickcount in ms
        uint64_t getTicks( void );

        friend class dpmutex_readlock;
        friend class dpmutex_writelock;

    };

}

#endif
