
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#include "dpshared.h"
#include "../dpmutex/dpmutex.h"
#include "../dpmutex/dpmutex_readlock.h"
#include "../dpmutex/dpmutex_writelock.h"
#include "dpshared_readlock.h"
#include "dpshared_writelock.h"
#include "dpshared_ref.h"

#if defined dpshared_debugout_all || defined dpshared_debug_lock_fails
#include <iostream>
#endif

namespace dp
{

        //ctor
        dpshared::dpshared( void )
        {
            this->m = new dpmutex();
        }

        //dtor
        dpshared::~dpshared( void )
        {
            delete this->m;
        }

        //generate readlock
        dpshared_readlock *dpshared::genReadLock( dpmutex_readlock *ml )
        {
            return new dpshared_readlock( this, ml );
        }

        //generate writelock
        dpshared_writelock *dpshared::genWriteLock( dpmutex_writelock *ml )
        {
            return new dpshared_writelock( this, ml );
        }

        //attempt readlock
        dpshared_readlock *dpshared::_usemacro_tryReadLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpmutex_readlock *ml;
            dpshared_readlock *l;

            ml = dpmutex_tryReadLock( this->m );
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                return 0;
            }

            l = this->genReadLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << "dpshared lock(read) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( cfile_macro, line_macro, cfunc_macro );
#endif
            return l;
        }

        //attempt writelock
        dpshared_writelock *dpshared::_usemacro_tryWriteLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpmutex_writelock *ml;
            dpshared_writelock *l;

            ml = dpmutex_tryWriteLock( this->m );
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                return 0;
            }

            l = this->genWriteLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << "dpshared lock(write) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
            return l;
        }

        //attempt readlock until timeout in milliseconds
        dpshared_readlock *dpshared::_usemacro_tryReadLock( unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    )
        {
            dpmutex_readlock *ml;
            dpshared_readlock *l;

            ml = dpmutex_tryReadLock_timeout( this->m, timeout_ms );
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                return 0;
            }

            l = this->genReadLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << "dpshared lock(read) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( cfile_macro, line_macro, cfunc_macro );
#endif
            return l;
        }

        //attempt writelock until timeout in milliseconds
        dpshared_writelock *dpshared::_usemacro_tryWriteLock( unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    )
        {
            dpmutex_writelock *ml;
            dpshared_writelock *l;

            ml = dpmutex_tryWriteLock_timeout( this->m, timeout_ms );
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                return 0;
            }

            l = this->genWriteLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << "dpshared lock(write) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
            return l;
        }

        //attempt readlock forever
        dpshared_readlock *dpshared::_usemacro_readLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpmutex_readlock *ml;
            dpshared_readlock *l;

            ml = dpmutex_readLock_block( this->m );
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                return 0;
            }

            l = this->genReadLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << "dpshared lock(read) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( cfile_macro, line_macro, cfunc_macro );
#endif
            return l;
        }

        //attempt writelock forever
        dpshared_writelock *dpshared::_usemacro_writeLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpmutex_writelock *ml;
            dpshared_writelock *l;

            ml = dpmutex_writeLock_block( this->m );
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                return 0;
            }

            l = this->genWriteLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << "dpshared lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << "dpshared lock(write) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
            return l;
        }

}

