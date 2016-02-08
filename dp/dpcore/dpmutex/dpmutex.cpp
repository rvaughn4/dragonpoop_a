
/*
mutex implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the mutex
*/

#include "dpmutex.h"
#include "dpspinlock.h"
#include "dpmutex_readlock.h"
#include "dpmutex_writelock.h"
#include <chrono>

#if defined dpmutex_debugout_all || defined dpmutex_debug_lock_fails
#include <iostream>
#endif

namespace dp
{

        //ctor
        dpmutex::dpmutex( void )
        {
            this->mm = 0;
            this->slk = new dpspinlock();
        }

        //ctor
        dpmutex::dpmutex( dpmutexmaster *mm )
        {
            this->mm = mm;
            this->slk = new dpspinlock();
        }

        //dtor
        dpmutex::~dpmutex( void )
        {
            delete this->slk;
        }

        //attempt readlock
        dpmutex_readlock *dpmutex::_usemacro_tryReadLock(
#ifdef dpmutex_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpmutex_readlock *l;

            if( this->wlock_ctr > 0 )
                return 0;

            this->slk->lock();
            if( this->wlock_ctr > 0 )
            {
                this->slk->unlock();
                return 0;
            }

#ifdef dpmutex_debug
            l = new dpmutex_readlock( this, cfile_macro, line_macro, cfunc_macro );
#else
            l = new dpmutex_readlock( this );
#endif
            if( !l )
            {
                this->slk->unlock();
                return 0;
            }

            this->rlock_ctr++;
            this->slk->unlock();

#ifdef dpmutex_debugout_all
            std::cout << "Mutex locked(read) at " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif

            return l;
        }

        //attempt writelock
        dpmutex_writelock *dpmutex::_usemacro_tryWriteLock(
#ifdef dpmutex_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpmutex_writelock *l;

            if( this->wlock_ctr > 0 )
                return 0;
            if( this->rlock_ctr > 0 )
                return 0;

            this->slk->lock();
            if( this->wlock_ctr > 0 )
            {
                this->slk->unlock();
                return 0;
            }
            if( this->rlock_ctr > 0 )
            {
                this->slk->unlock();
                return 0;
            }

#ifdef dpmutex_debug
            l = new dpmutex_writelock( this, cfile_macro, line_macro, cfunc_macro );
#else
            l = new dpmutex_writelock( this );
#endif
            if( !l )
            {
                this->slk->unlock();
                return 0;
            }

            this->wlock_ctr++;
            this->slk->unlock();

#ifdef dpmutex_debugout_all
            std::cout << "Mutex locked(write) at " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif

            return l;
        }

        //attempt readlock until timeout in milliseconds
        dpmutex_readlock *dpmutex::_usemacro_tryReadLock( unsigned int timeout_ms
#ifdef dpmutex_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    )
        {
            uint64_t t_start, t_now, t_stop;
            dpmutex_readlock *l;

#ifdef dpmutex_debug
            l = this->_usemacro_tryReadLock( cfile_macro, line_macro, cfunc_macro );
#else
            l = this->_usemacro_tryReadLock();
#endif
            if( l )
                return l;

            t_start = this->getTicks();
            t_stop = t_start + (uint64_t)timeout_ms;

            do
            {
#ifdef dpmutex_debug
                l = this->_usemacro_tryReadLock( cfile_macro, line_macro, cfunc_macro );
#else
                l = this->_usemacro_tryReadLock();
#endif
                if( l )
                    return l;

                t_now = this->getTicks();
            }
            while( !l && t_now < t_stop );

#if defined dpmutex_debugout_all || defined dpmutex_debug_lock_fails
            std::cout << "Mutex !!NOT!! locked(read) at " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
            return 0;
        }

        //attempt writelock until timeout in milliseconds
        dpmutex_writelock *dpmutex::_usemacro_tryWriteLock( unsigned int timeout_ms
#ifdef dpmutex_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    )
        {
            uint64_t t_start, t_now, t_stop;
            dpmutex_writelock *l;

#ifdef dpmutex_debug
            l = this->_usemacro_tryWriteLock( cfile_macro, line_macro, cfunc_macro );
#else
            l = this->_usemacro_tryWriteLock();
#endif
            if( l )
                return l;

            t_start = this->getTicks();
            t_stop = t_start + (uint64_t)timeout_ms;
            do
            {
#ifdef dpmutex_debug
                l = this->_usemacro_tryWriteLock( cfile_macro, line_macro, cfunc_macro );
#else
                l = this->_usemacro_tryWriteLock();
#endif
                if( l )
                    return l;

                t_now = this->getTicks();
            }
            while( !l && t_now < t_stop );

#if defined dpmutex_debugout_all || defined dpmutex_debug_lock_fails
            std::cout << "Mutex !!NOT!! locked(write) at " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
            return 0;
        }

        //attempt readlock forever
        dpmutex_readlock *dpmutex::_usemacro_readLock(
#ifdef dpmutex_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpmutex_readlock *l = 0;

            do
            {
#ifdef dpmutex_debug
                l = this->_usemacro_tryReadLock( cfile_macro, line_macro, cfunc_macro );
#else
                l = this->_usemacro_tryReadLock();
#endif
            }
            while( !l );

            return l;
        }

        //attempt writelock forever
        dpmutex_writelock *dpmutex::_usemacro_writeLock(
#ifdef dpmutex_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpmutex_writelock *l = 0;

            do
            {
#ifdef dpmutex_debug
                l = this->_usemacro_tryWriteLock( cfile_macro, line_macro, cfunc_macro );
#else
                l = this->_usemacro_tryWriteLock();
#endif
            }
            while( !l );

            return l;
        }

        //unlock
        void dpmutex::unlock(
                    dpmutex_readlock *l
#ifdef dpmutex_debug
                    ,
                    const char *cfile_macro,
                    unsigned int line_macro,
                    const char *cfunc_macro
#endif
                    )
        {

#ifdef dpmutex_debugout_all
            std::cout << "Mutex unlocked(read) at " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif

            this->slk->lock();
            this->rlock_ctr--;
            this->slk->unlock();
        }

        //unlock
        void dpmutex::unlock(
                    dpmutex_writelock *l
#ifdef dpmutex_debug
                    ,
                    const char *cfile_macro,
                    unsigned int line_macro,
                    const char *cfunc_macro
#endif
                    )
        {

#ifdef dpmutex_debugout_all
            std::cout << "Mutex unlocked(write) at " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif

            this->slk->lock();
            this->wlock_ctr--;
            this->slk->unlock();
        }

        //returns current epoch time in seconds
        uint64_t dpmutex::getEpoch( void )
        {
            std::chrono::time_point<std::chrono::steady_clock> tp_now;
            std::chrono::steady_clock::duration d_s;

            tp_now = std::chrono::steady_clock::now();
            d_s = tp_now.time_since_epoch();

            return d_s.count() * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
        }

        //returns tickcount in ms
        uint64_t dpmutex::getTicks( void )
        {
            std::chrono::time_point<std::chrono::steady_clock> tp_now;
            std::chrono::steady_clock::duration d_s;

            tp_now = std::chrono::steady_clock::now();
            d_s = tp_now.time_since_epoch();

            return d_s.count() * 1000 * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
        }

}
