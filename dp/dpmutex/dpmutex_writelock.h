
#ifndef dpmutex_writelock_h
#define dpmutex_writelock_h

#include "dpmutexdefines.h"

namespace dp
{

    class dpmutex;

    class dpmutex_writelock
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
        dpmutex_writelock(
                         dpmutex *m
#ifdef dpmutex_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                          );
        //dtor
        virtual ~dpmutex_writelock( void );

    };

}

#endif


