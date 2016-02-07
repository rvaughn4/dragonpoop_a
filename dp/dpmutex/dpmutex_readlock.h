
#ifndef dpmutex_readlock_h
#define dpmutex_readlock_h

#include "dpmutexdefines.h"

namespace dp
{

    class dpmutex;

    class dpmutex_readlock
    {

    private:

        dpmutex *m;
#ifdef dpmutex_debug
                                        const char *cfile_macro;
                                        unsigned int line_macro;
                                        const char *cfunc_macro;
#endif

    protected:

    public:

        //ctor
        dpmutex_readlock(
                         dpmutex *m
#ifdef dpmutex_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                          );
        //dtor
        virtual ~dpmutex_readlock( void );

    };

}

#endif

