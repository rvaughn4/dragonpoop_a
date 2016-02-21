/*
represents the lifecycle of a writelock on a dpshared
this object is returned from a dpshared when writelocked
deleting this object releases the writelock on the dpshared
*/

#ifndef dpshared_writelock_h
#define dpshared_writelock_h

#include "dpshareddefines.h"

namespace dp
{

    class dpshared;
    class dpmutex_writelock;
    class dpshared_ref;

    class dpshared_writelock
    {

    private:

        dpmutex_writelock *ml;
        dpshared *p;
#ifdef dpshared_debug
        const char *cname;
        const char *cfile_macro;
        unsigned int line_macro;
        const char *cfunc_macro;
#endif

    protected:

    public:

        //ctor
        dpshared_writelock( dpshared *p, dpmutex_writelock *ml );
        //dtor
        virtual ~dpshared_writelock( void );
        //set debug stuff
        void setDebug(
#ifdef dpshared_debug
        const char *cname,
        const char *cfile_macro,
        unsigned int line_macro,
        const char *cfunc_macro
#else
        void
#endif
                    );
        //get reference
        dpshared_ref *getRef( void );
        //called to run
        void run( void );

    };

}

#endif



