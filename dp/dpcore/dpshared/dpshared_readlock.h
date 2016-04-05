/*
represents the lifecycle of a readlock on a dpshared
this object is returned from a dpshared when readlocked
deleting this object releases the readlock on the dpshared
*/

#ifndef dpshared_readlock_h
#define dpshared_readlock_h

#include "dpshareddefines.h"

namespace dp
{

    class dpshared;
    class dpmutex_readlock;
    class dpshared_ref;

    class dpshared_readlock
    {

    private:

        dpmutex_readlock *ml;
        dpshared *p;
#ifdef dpshared_debug
        const char *cname;
        const char *cfile_macro;
        unsigned int line_macro;
        const char *cfunc_macro;
#endif

    protected:

        //dtor
        virtual ~dpshared_readlock( void );

    public:

        //ctor
        dpshared_readlock( dpshared *p, dpmutex_readlock *ml );
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
        //override to test type for safe syncing, be sure to call base class first!
        bool isSyncType( const char *ctypename );


        friend class dpshared_guard;
        friend class dpshared;
    };

}

#endif


