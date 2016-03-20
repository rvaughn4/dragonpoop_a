
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpshared_ref.h"
#include "dpshared.h"
#include "dpshared_readlock.h"
#include "dpshared_writelock.h"
#include "dpshared_guard.h"
#include "dpshared_ref_kernel.h"

namespace dp
{

        //ctor
        dpshared_ref::dpshared_ref( dpshared *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
        {
            this->p = p;
            this->k = *k;
            this->t_sync = *t_sync;
        }

        //dtor
        dpshared_ref::~dpshared_ref( void )
        {

        }

        //attempt readlock
        dpshared_readlock *dpshared_ref::_usemacro_tryReadLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpshared *p;

            if( !this->isLinked() )
                return 0;

            p = this->p;
            return p->_usemacro_tryReadLock(
#ifdef dpshared_debug
                                        cfile_macro, line_macro, cfunc_macro
#endif
                                                  );
        }

        //attempt writelock
        dpshared_writelock *dpshared_ref::_usemacro_tryWriteLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpshared *p;

            if( !this->isLinked() )
                return 0;

            p = this->p;
            return p->_usemacro_tryWriteLock(
#ifdef dpshared_debug
                                        cfile_macro, line_macro, cfunc_macro
#endif
                                                  );
        }

        //attempt readlock until timeout in milliseconds
        dpshared_readlock *dpshared_ref::_usemacro_tryReadLock( unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    )
        {
            dpshared *p;

            if( !this->isLinked() )
                return 0;

            p = this->p;
            return p->_usemacro_tryReadLock( timeout_ms
#ifdef dpshared_debug
                                        , cfile_macro, line_macro, cfunc_macro
#endif
                                                  );
        }

        //attempt writelock until timeout in milliseconds
        dpshared_writelock *dpshared_ref::_usemacro_tryWriteLock( unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    )
        {
            dpshared *p;

            if( !this->isLinked() )
                return 0;
            p = this->p;
            return p->_usemacro_tryWriteLock( timeout_ms
#ifdef dpshared_debug
                                        , cfile_macro, line_macro, cfunc_macro
#endif
                                                  );
        }

        //attempt readlock forever
        dpshared_readlock *dpshared_ref::_usemacro_readLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpshared *p;

            if( !this->isLinked() )
                return 0;
            p = this->p;
            return p->_usemacro_readLock(
#ifdef dpshared_debug
                                        cfile_macro, line_macro, cfunc_macro
#endif
                                                  );
        }

        //attempt writelock forever
        dpshared_writelock *dpshared_ref::_usemacro_writeLock(
#ifdef dpshared_debug
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#else
                                        void
#endif
                                    )
        {
            dpshared *p;

            if( !this->isLinked() )
                return 0;
            p = this->p;
            return p->_usemacro_writeLock(
#ifdef dpshared_debug
                                        cfile_macro, line_macro, cfunc_macro
#endif
                                                  );
        }

        //returns true if linked
        bool dpshared_ref::isLinked( void )
        {
            if( !this->p )
                return 0;
            if( !this->k || this->k.unique() )
                return 0;
            return ( *this->k ).isLinked();
        }

        //unlink ref
        void dpshared_ref::unlink( void )
        {
            this->p = 0;
        }

        //get reference
        dpshared_ref *dpshared_ref::getRef( void )
        {
            dpshared *p;
            if( !this->isLinked() )
                return 0;
            p = this->p;
            return p->getRef();
        }

        //compares parent
        bool dpshared_ref::isParent( dpshared *p )
        {
            return p == this->p;
        }

}



