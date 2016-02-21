
/*
resource allocation through instatiation
*/

#include "dpshared_guard.h"
#include "dpshared.h"
#include "dpshared_ref.h"
#include "dpshared_readlock.h"
#include "dpshared_writelock.h"

namespace dp
{

    //ctor
    dpshared_guard::dpshared_guard( void )
    {

    }

    //dtor
    dpshared_guard::~dpshared_guard( void )
    {
        this->releaseRefs();
        this->releaseReadLocks();
        this->releaseWriteLocks();
    }

    //releases ref
    void dpshared_guard::release( dpshared_ref *p )
    {
        std::list<dpshared_ref *> *l;
        std::list<dpshared_ref *>::iterator i;
        dpshared_ref *r;
        bool d;

        d = 0;
        l = &this->refs;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            if( r == p )
                d = 1;
        }
        if( !d )
            return;

        l->remove( p );
        delete p;
    }

    //releases readlock
    void dpshared_guard::release( dpshared_readlock *p )
    {
        std::list<dpshared_readlock *> *l;
        std::list<dpshared_readlock *>::iterator i;
        dpshared_readlock *r;
        bool d;

        d = 0;
        l = &this->rls;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            if( r == p )
                d = 1;
        }
        if( !d )
            return;

        l->remove( p );
        delete p;
    }

    //releases writelock
    void dpshared_guard::release( dpshared_writelock *p )
    {
        std::list<dpshared_writelock *> *l;
        std::list<dpshared_writelock *>::iterator i;
        dpshared_writelock *r;
        bool d;

        d = 0;
        l = &this->wls;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            if( r == p )
                d = 1;
        }
        if( !d )
            return;

        l->remove( p );
        delete p;
    }

    //release all refs
    void dpshared_guard::releaseRefs( void )
    {
        std::list<dpshared_ref *> *l, d;
        std::list<dpshared_ref *>::iterator i;
        dpshared_ref *r;

        l = &this->refs;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            d.push_back( r );
        }
        l->clear();

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            delete r;
        }
    }

    //release all readlocks
    void dpshared_guard::releaseReadLocks( void )
    {
        std::list<dpshared_readlock *> *l, d;
        std::list<dpshared_readlock *>::iterator i;
        dpshared_readlock *r;

        l = &this->rls;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            d.push_back( r );
        }
        l->clear();

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            delete r;
        }
    }

    //release all writelocks
    void dpshared_guard::releaseWriteLocks( void )
    {
        std::list<dpshared_writelock *> *l, d;
        std::list<dpshared_writelock *>::iterator i;
        dpshared_writelock *r;

        l = &this->wls;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            d.push_back( r );
        }
        l->clear();

        l = &d;
        for( i = l->begin(); i != l->end(); ++i )
        {
            r = *i;
            delete r;
        }
    }

    //inner ref alg
    dpshared_ref *dpshared_guard::_getRef( dpshared_ref *r )
    {
        if( !r )
            return 0;
        this->refs.push_back( r );
        return r;
    }

    //get ref
    dpshared_ref *dpshared_guard::getRef( dpshared *p )
    {
        return this->_getRef( p->getRef() );
    }

    //get ref
    dpshared_ref *dpshared_guard::getRef( dpshared_ref *p )
    {
        return this->_getRef( p->getRef() );
    }

    //get ref
    dpshared_ref *dpshared_guard::getRef( dpshared_readlock *p )
    {
        return this->_getRef( p->getRef() );
    }

    //get ref
    dpshared_ref *dpshared_guard::getRef( dpshared_writelock *p )
    {
        return this->_getRef( p->getRef() );
    }

    //attempt readlock
    dpshared_readlock *dpshared_guard::_guard_tryReadLock( dpshared *p
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_readlock *r;

        r = p->_usemacro_tryReadLock(
#ifdef dpshared_debug
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->rls.push_back( r );
        return r;
    }

    //attempt readlock
    dpshared_readlock *dpshared_guard::_guard_tryReadLock( dpshared_ref *p
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_readlock *r;

        r = p->_usemacro_tryReadLock(
#ifdef dpshared_debug
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->rls.push_back( r );
        return r;
    }

    //attempt readlock
    dpshared_readlock *dpshared_guard::_guard_tryReadLock( dpshared *p, unsigned int timeout_ms
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_readlock *r;

        r = p->_usemacro_tryReadLock( timeout_ms
#ifdef dpshared_debug
                                    ,
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->rls.push_back( r );
        return r;
    }

    //attempt readlock
    dpshared_readlock *dpshared_guard::_guard_tryReadLock( dpshared_ref *p, unsigned int timeout_ms
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_readlock *r;

        r = p->_usemacro_tryReadLock( timeout_ms
#ifdef dpshared_debug
                                    ,
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->rls.push_back( r );
        return r;
    }

    //attempt readlock
    dpshared_readlock *dpshared_guard::_guard_readLock( dpshared *p
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_readlock *r;

        r = p->_usemacro_readLock(
#ifdef dpshared_debug
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->rls.push_back( r );
        return r;
    }

    //attempt readlock
    dpshared_readlock *dpshared_guard::_guard_readLock( dpshared_ref *p
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_readlock *r;

        r = p->_usemacro_readLock(
#ifdef dpshared_debug
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->rls.push_back( r );
        return r;
    }

    //attempt writelock
    dpshared_writelock *dpshared_guard::_guard_tryWriteLock( dpshared *p
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_writelock *r;

        r = p->_usemacro_tryWriteLock(
#ifdef dpshared_debug
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->wls.push_back( r );
        return r;
    }

    //attempt writelock
    dpshared_writelock *dpshared_guard::_guard_tryWriteLock( dpshared_ref *p
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_writelock *r;

        r = p->_usemacro_tryWriteLock(
#ifdef dpshared_debug
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->wls.push_back( r );
        return r;
    }

    //attempt writelock
    dpshared_writelock *dpshared_guard::_guard_tryWriteLock( dpshared *p, unsigned int timeout_ms
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_writelock *r;

        r = p->_usemacro_tryWriteLock( timeout_ms
#ifdef dpshared_debug
                                    ,
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->wls.push_back( r );
        return r;
    }

    //attempt writelock
    dpshared_writelock *dpshared_guard::_guard_tryWriteLock( dpshared_ref *p, unsigned int timeout_ms
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_writelock *r;

        r = p->_usemacro_tryWriteLock( timeout_ms
#ifdef dpshared_debug
                                    ,
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->wls.push_back( r );
        return r;
    }

    //attempt writelock
    dpshared_writelock *dpshared_guard::_guard_writeLock( dpshared *p
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_writelock *r;

        r = p->_usemacro_writeLock(
#ifdef dpshared_debug
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->wls.push_back( r );
        return r;
    }

    //attempt writelock
    dpshared_writelock *dpshared_guard::_guard_writeLock( dpshared_ref *p
#ifdef dpshared_debug
                                    ,
                                    const char *cfile_macro,
                                    unsigned int line_macro,
                                    const char *cfunc_macro
#endif
                                )
    {
        dpshared_writelock *r;

        r = p->_usemacro_writeLock(
#ifdef dpshared_debug
                                    cfile_macro,
                                    line_macro,
                                    cfunc_macro
#endif
                                     );
        if( !r )
            return 0;

        this->wls.push_back( r );
        return r;
    }

}




