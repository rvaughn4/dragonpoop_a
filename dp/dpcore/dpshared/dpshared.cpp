
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
#include "dpshared_guard.h"

#if defined dpshared_debugout_all || defined dpshared_debug_lock_fails
#include <iostream>
#endif

namespace dp
{

        //ctor
        dpshared::dpshared( void )
        {
            this->m = new dpmutex();
            this->rsync = 0;

            std::shared_ptr<std::atomic<uint64_t>> tt( new std::atomic<uint64_t>() );
            this->t_sync = tt;
            *( this->t_sync.get() ) = 0;

            std::shared_ptr<dpshared_ref_kernel> kk( new dpshared_ref_kernel() );
            this->k = kk;

            this->setName( "Shared Object" );

#if defined dpshared_debug
            this->cfile_macro = "";
            this->line_macro = 0;
            this->cfunc_macro = "";
#endif
        }

        //dtor
        dpshared::~dpshared( void )
        {
            delete this->m;
            ( *this->k ).unlink();
            if( this->rsync )
                delete this->rsync;
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

        //generate ref
        dpshared_ref *dpshared::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
        {
            return new dpshared_ref( this, k, t_sync );
        }

        //get reference
        dpshared_ref *dpshared::getRef( void )
        {
            dpshared_ref *r = this->genRef( &this->k, &this->t_sync );
            return r;
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

#if defined dpmutex_debug && defined dpshared_debug
            ml = this->m->_usemacro_tryReadLock( cfile_macro, line_macro, cfunc_macro );
#else
            ml = dpmutex_tryReadLock( this->m );
#endif
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                return 0;
            }

            l = this->genReadLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << this->cname << " lock(read) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( this->cname, cfile_macro, line_macro, cfunc_macro );
#endif

#if defined dpshared_debug
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
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

#if defined dpmutex_debug && defined dpshared_debug
            ml = this->m->_usemacro_tryWriteLock( cfile_macro, line_macro, cfunc_macro );
#else
            ml = dpmutex_tryWriteLock( this->m );
#endif
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                return 0;
            }

            l = this->genWriteLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << this->cname << " lock(write) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( this->cname, cfile_macro, line_macro, cfunc_macro );
#endif

#if defined dpshared_debug
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
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

#if defined dpmutex_debug && defined dpshared_debug
            ml = this->m->_usemacro_tryReadLock( timeout_ms, cfile_macro, line_macro, cfunc_macro );
#else
            ml = dpmutex_tryReadLock_timeout( this->m, timeout_ms );
#endif
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                return 0;
            }

            l = this->genReadLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << this->cname << " lock(read) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( this->cname, cfile_macro, line_macro, cfunc_macro );
#endif

#if defined dpshared_debug
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
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

#if defined dpmutex_debug && defined dpshared_debug
            ml = this->m->_usemacro_tryWriteLock( timeout_ms, cfile_macro, line_macro, cfunc_macro );
#else
            ml = dpmutex_tryWriteLock_timeout( this->m, timeout_ms );
#endif
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                return 0;
            }

            l = this->genWriteLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << this->cname << " lock(write) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( this->cname, cfile_macro, line_macro, cfunc_macro );
#endif

#if defined dpshared_debug
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
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


#if defined dpmutex_debug && defined dpshared_debug
            ml = this->m->_usemacro_readLock( cfile_macro, line_macro, cfunc_macro );
#else
            ml = dpmutex_readLock_block( this->m );
#endif
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                return 0;
            }

            l = this->genReadLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(read) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << this->cname << " lock(read) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( this->cname, cfile_macro, line_macro, cfunc_macro );
#endif

#if defined dpshared_debug
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
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

#if defined dpmutex_debug && defined dpshared_debug
            ml = this->m->_usemacro_writeLock( cfile_macro, line_macro, cfunc_macro );
#else
            ml = dpmutex_writeLock_block( this->m );
#endif
            if( !ml )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                return 0;
            }

            l = this->genWriteLock( ml );
            if( !l )
            {
#ifdef dpshared_debug_lock_fails
                std::cout << this->cname << " lock(write) !!!FAIL!!! " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
                std::cout << this->cfile_macro << " " << this->line_macro << " " << this->cfunc_macro << " has lock!\r\n";
#endif
                delete ml;
                return 0;
            }

#ifdef dpshared_debugout_all
                std::cout << this->cname << " lock(write) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
#ifdef dpshared_debug
            l->setDebug( this->cname, cfile_macro, line_macro, cfunc_macro );
#endif

#if defined dpshared_debug
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
#endif
            return l;
        }

        //set object name for debug output
        void dpshared::setName( const char *cname )
        {
#ifdef dpshared_debug
            this->cname = cname;
#endif
        }

        //set shared object to sync by
        void dpshared::setSync( dpshared *psync )
        {
            dpshared_readlock *l;

            l = dpshared_tryReadLock_timeout( psync, 3000 );
            if( !l )
                return;

            this->setSync( l );

            delete l;
        }

        //set shared object to sync by
        void dpshared::setSync( dpshared_ref *psync )
        {
            dpshared_readlock *l;

            l = dpshared_tryReadLock_timeout( psync, 3000 );
            if( !l )
                return;

            this->setSync( l );

            delete l;
        }

        //set shared object to sync by
        void dpshared::setSync( dpshared_readlock *psync )
        {
            if( this->rsync )
                delete this->rsync;

            this->rsync = psync->getRef();
        }

        //set shared object to sync by
        void dpshared::setSync( dpshared_writelock *psync )
        {
            if( this->rsync )
                delete this->rsync;

            this->rsync = psync->getRef();
        }

        //sync with shared object stored inside if internal time mismatched
        void dpshared::sync( void )
        {
            dpshared_readlock *l;
            uint64_t tr, tt;

            if( !this->rsync )
                return;

            tt = *( this->t_sync.get() );
            tr = *( this->rsync->t_sync.get() );
            if( tt == tr )
                return;

            l = dpshared_tryReadLock_timeout( this->rsync, 30 );
            if( !l )
                return;

            this->onSync( l );
            *( this->t_sync.get() ) = tr;

            delete l;
        }

        //update internal time to cause objects to sync
        void dpshared::update( void )
        {
            *( this->t_sync.get() ) = this->m->getTicks();
        }

        //override to handle sync copy, be sure to call base class first!
        void dpshared::onSync( dpshared_readlock *psync )
        {

        }

        //override to test type for safe syncing, be sure to call base class first!
        bool dpshared::isSyncType( const char *ctypename )
        {
            std::string s( ctypename );
            return s.compare( "dpshared" ) == 0;
        }

        //called to run
        void dpshared::run( dpshared_writelock *wl )
        {
            if( this->rsync )
                this->sync();
            this->onRun( wl );
        }

        //override to handle processing
        void dpshared::onRun( dpshared_writelock *wl )
        {

        }

        //returns current epoch time in seconds
        uint64_t dpshared::getEpoch( void )
        {
            return this->m->getEpoch();
        }

        //returns tickcount in ms
        uint64_t dpshared::getTicks( void )
        {
            return this->m->getTicks();
        }

        //unlink
        void dpshared::unlink( void )
        {
            dpshared_guard g;
            dpshared_writelock *l;

            l = dpshared_guard_tryWriteLock_timeout( g, this, 5000 );
            ( *this->k ).unlink();
            g.release( l );

            l = dpshared_guard_tryWriteLock_timeout( g, this, 5000 );
            ( *this->k ).unlink();
            g.release( l );
        }

}

