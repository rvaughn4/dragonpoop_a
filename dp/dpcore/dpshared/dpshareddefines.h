
#ifndef dpshareddefines_h
#define dpshareddefines_h

#include "../../dpdefines.h"
#include "../dpmutex/dpmutexdefines.h"

#if defined dpshared_debugout_all || defined dpshared_debug_lock_fails
    #ifndef dpshared_debug
        #define dpshared_debug
    #endif
#endif

#ifdef dpshared_debug
    #define dpshared_tryReadLock( x ) x->_usemacro_tryReadLock( __FILE__, __LINE__, __func__ )
    #define dpshared_tryWriteLock( x ) x->_usemacro_tryWriteLock( __FILE__, __LINE__, __func__ )
    #define dpshared_tryReadLock_timeout( x, timeout_ms ) x->_usemacro_tryReadLock( timeout_ms, __FILE__, __LINE__, __func__ )
    #define dpshared_tryWriteLock_timeout( x, timeout_ms ) x->_usemacro_tryWriteLock( timeout_ms, __FILE__, __LINE__, __func__ )
    #define dpshared_readLock_block( x ) x->_usemacro_readLock( __FILE__, __LINE__, __func__ )
    #define dpshared_writeLock_block( x ) x->_usemacro_writeLock( __FILE__, __LINE__, __func__ )
#else
    #define dpshared_tryReadLock( x ) x->_usemacro_tryReadLock()
    #define dpshared_tryWriteLock( x ) x->_usemacro_tryWriteLock()
    #define dpshared_tryReadLock_timeout( x, timeout_ms ) x->_usemacro_tryReadLock( timeout_ms )
    #define dpshared_tryWriteLock_timeout( x, timeout_ms ) x->_usemacro_tryWriteLock( timeout_ms )
    #define dpshared_readLock_block( x ) x->_usemacro_readLock()
    #define dpshared_writeLock_block( x ) x->_usemacro_writeLock()
#endif


#ifdef dpshared_debug
    #define dpshared_guard_tryReadLock( x, y ) x._guard_tryReadLock( y, __FILE__, __LINE__, __func__ )
    #define dpshared_guard_tryWriteLock( x, y ) x._guard_tryWriteLock( y, __FILE__, __LINE__, __func__ )
    #define dpshared_guard_tryReadLock_timeout( x, y, timeout_ms ) x._guard_tryReadLock( y, timeout_ms, __FILE__, __LINE__, __func__ )
    #define dpshared_guard_tryWriteLock_timeout( x, y, timeout_ms ) x._guard_tryWriteLock( y, timeout_ms, __FILE__, __LINE__, __func__ )
    #define dpshared_guard_readLock_block( x, y ) x._guard_readLock( y, __FILE__, __LINE__, __func__ )
    #define dpshared_guard_writeLock_block( x, y ) x._guard_writeLock( y, __FILE__, __LINE__, __func__ )
#else
    #define dpshared_guard_tryReadLock( x, y ) x._guard_tryReadLock( y )
    #define dpshared_guard_tryWriteLock( x, y ) x._guard_tryWriteLock( y )
    #define dpshared_guard_tryReadLock_timeout( x, y, timeout_ms ) x._guard_tryReadLock( y, timeout_ms )
    #define dpshared_guard_tryWriteLock_timeout( x, y, timeout_ms ) x._guard_tryWriteLock( y, timeout_ms )
    #define dpshared_guard_readLock_block( x, y ) x._guard_readLock( y )
    #define dpshared_guard_writeLock_block( x, y ) x._guard_writeLock( y )
#endif


#endif


