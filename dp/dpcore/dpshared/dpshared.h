
/*
shared implementation, uses read write locking
returns a readlock or writelock object that handles the lifecycle of the lock
deleting the readlock or writelock object unlocks the shared
*/

#ifndef dpshared_h
#define dpshared_h

#include "dpshareddefines.h"
#include <atomic>

namespace dp
{

    class dpshared_ref;
    class dpshared_readlock;
    class dpshared_writelock;
    class dpmutex;

    class dpshared
    {

    private:

        dpmutex *m;

    protected:

    public:


        //ctor
        dpshared( void );
        //dtor
        virtual ~dpshared( void );
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


    };

}

#endif

