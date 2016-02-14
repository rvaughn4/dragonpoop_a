/*
represents the lifecycle of a readlock on a dpshared
this object is returned from a dpshared when readlocked
deleting this object releases the readlock on the dpshared
*/

#include "dpshared_readlock.h"
#include "dpshared.h"
#include "../dpmutex/dpmutex_readlock.h"
#ifdef dpshared_debug
#include <iostream>
#endif

namespace dp
{

        //ctor
        dpshared_readlock::dpshared_readlock( dpshared *p, dpmutex_readlock *ml )
        {
            this->p = p;
            this->ml = ml;
        }

        //dtor
        dpshared_readlock::~dpshared_readlock( void )
        {
            delete this->ml;
#ifdef dpshared_debugout_all
                std::cout << "dpshared unlock(read) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
        }

        //set debug stuff
        void dpshared_readlock::setDebug(
#ifdef dpshared_debug
        const char *cname,
        const char *cfile_macro,
        unsigned int line_macro,
        const char *cfunc_macro
#else
        void
#endif
                    )
        {
#ifdef dpshared_debug
            this->cname = cname;
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
#endif
        }

        //get reference
        dpshared_ref *dpshared_readlock::getRef( void )
        {
            return this->p->getRef();
        }

}



