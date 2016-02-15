
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpshared_ref_h
#define dpshared_ref_h

#include "dpshareddefines.h"
#include "dpshared_ref_kernel.h"
#include <memory>

namespace dp
{

    class dpshared;
    class dpshared_readlock;
    class dpshared_writelock;

    class dpshared_ref
    {

    private:

        dpshared *p;
        std::shared_ptr<dpshared_ref_kernel> k;
        std::shared_ptr< std::atomic<uint64_t> > t_sync;

    protected:

    public:


        //ctor
        dpshared_ref( dpshared *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //dtor
        virtual ~dpshared_ref( void );
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

        //returns true if linked
        bool isLinked( void );
        //unlink ref
        void unlink( void );
        //get reference
        dpshared_ref *getRef( void );

    };

}

#endif


