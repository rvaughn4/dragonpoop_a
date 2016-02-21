
/*
resource allocation through instatiation
*/

#ifndef dpshared_guard_h
#define dpshared_guard_h

#include "dpshareddefines.h"
#include <list>

namespace dp
{

    class dpshared;
    class dpshared_ref;
    class dpshared_readlock;
    class dpshared_writelock;

    class dpshared_guard
    {

    private:

        std::list<dpshared_ref *> refs;
        std::list<dpshared_readlock *> rls;
        std::list<dpshared_writelock *> wls;

        //inner ref alg
        dpshared_ref *_getRef( dpshared_ref *r );

    protected:

    public:

        //ctor
        dpshared_guard( void );
        //dtor
        virtual ~dpshared_guard( void );
        //releases ref
        void release( dpshared_ref *p );
        //releases readlock
        void release( dpshared_readlock *p );
        //releases writelock
        void release( dpshared_writelock *p );
        //release all refs
        void releaseRefs( void );
        //release all readlocks
        void releaseReadLocks( void );
        //release all writelocks
        void releaseWriteLocks( void );
        //get ref
        dpshared_ref *getRef( dpshared *p );
        //get ref
        dpshared_ref *getRef( dpshared_ref *p );
        //get ref
        dpshared_ref *getRef( dpshared_readlock *p );
        //get ref
        dpshared_ref *getRef( dpshared_writelock *p );
        //attempt readlock
        dpshared_readlock *_guard_tryReadLock( dpshared *p
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt readlock
        dpshared_readlock *_guard_tryReadLock( dpshared_ref *p
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt readlock
        dpshared_readlock *_guard_tryReadLock( dpshared *p, unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt readlock
        dpshared_readlock *_guard_tryReadLock( dpshared_ref *p, unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt readlock
        dpshared_readlock *_guard_readLock( dpshared *p
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt readlock
        dpshared_readlock *_guard_readLock( dpshared_ref *p
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt writelock
        dpshared_writelock *_guard_tryWriteLock( dpshared *p
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt writelock
        dpshared_writelock *_guard_tryWriteLock( dpshared_ref *p
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt writelock
        dpshared_writelock *_guard_tryWriteLock( dpshared *p, unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt writelock
        dpshared_writelock *_guard_tryWriteLock( dpshared_ref *p, unsigned int timeout_ms
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt writelock
        dpshared_writelock *_guard_writeLock( dpshared *p
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );
        //attempt writelock
        dpshared_writelock *_guard_writeLock( dpshared_ref *p
#ifdef dpshared_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                                    );


    };

}

#endif



