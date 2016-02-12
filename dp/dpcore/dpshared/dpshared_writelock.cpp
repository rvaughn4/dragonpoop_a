/*
represents the lifecycle of a writelock on a dpshared
this object is returned from a dpshared when writelocked
deleting this object releases the writelock on the dpshared
*/

#include "dpshared_writelock.h"
#include "dpshared.h"
#include "../dpmutex/dpmutex_writelock.h"

namespace dp
{

        //ctor
        dpshared_writelock::dpshared_writelock( dpshared *p, dpmutex_writelock *ml )
        {
            this->p = p;
            this->ml = ml;
        }

        //dtor
        dpshared_writelock::~dpshared_writelock( void )
        {
            delete this->ml;
#ifdef dpshared_debugout_all
                std::cout << "dpshared unlock(write) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
        }

        //set debug stuff
        void dpshared_writelock::setDebug(
#ifdef dpshared_debug
        const char *cfile_macro,
        unsigned int line_macro,
        const char *cfunc_macro
#else
        void
#endif
                    )
        {
#ifdef dpshared_debug
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
#endif
        }

}




