
#ifndef dpmutexdefines_h
#define dpmutexdefines_h

#include "../../dpdefines.h"

#if defined dpmutex_debugout_all || defined dpmutex_debug_lock_fails
    #ifndef dpmutex_debug
        #define dpmutex_debug
    #endif
#endif

#ifdef dpmutex_debug
    #define dpmutex_tryReadLock( x ) x->_usemacro_tryReadLock( __FILE__, __LINE__, __func__ )
    #define dpmutex_tryWriteLock( x ) x->_usemacro_tryWriteLock( __FILE__, __LINE__, __func__ )
    #define dpmutex_tryReadLock_timeout( x, timeout_ms ) x->_usemacro_tryReadLock( timeout_ms, __FILE__, __LINE__, __func__ )
    #define dpmutex_tryWriteLock_timeout( x, timeout_ms ) x->_usemacro_tryWriteLock( timeout_ms, __FILE__, __LINE__, __func__ )
    #define dpmutex_readLock_block( x ) x->_usemacro_readLock( __FILE__, __LINE__, __func__ )
    #define dpmutex_writeLock_block( x ) x->_usemacro_writeLock( __FILE__, __LINE__, __func__ )
#else
    #define dpmutex_tryReadLock( x ) x->_usemacro_tryReadLock()
    #define dpmutex_tryWriteLock( x ) x->_usemacro_tryWriteLock()
    #define dpmutex_tryReadLock_timeout( x, timeout_ms ) x->_usemacro_tryReadLock( timeout_ms )
    #define dpmutex_tryWriteLock_timeout( x, timeout_ms ) x->_usemacro_tryWriteLock( timeout_ms )
    #define dpmutex_readLock_block( x ) x->_usemacro_readLock()
    #define dpmutex_writeLock_block( x ) x->_usemacro_writeLock()
#endif

#endif

