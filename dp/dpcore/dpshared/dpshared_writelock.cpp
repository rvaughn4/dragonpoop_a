/*
represents the lifecycle of a writelock on a dpshared
this object is returned from a dpshared when writelocked
deleting this object releases the writelock on the dpshared
*/

#include "dpshareddefines.h"
#include "dpshared_writelock.h"
#include "dpshared.h"
#include "../dpmutex/dpmutex_writelock.h"
#ifdef dpshared_debug
#include <iostream>
#endif

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
                std::cout << this->cname << " unlock(write) " << cfile_macro << " " << line_macro << " " << cfunc_macro << "\r\n";
#endif
        }

        //set debug stuff
        void dpshared_writelock::setDebug(
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
        dpshared_ref *dpshared_writelock::getRef( void )
        {
            return this->p->getRef();
        }

        //called to run
        void dpshared_writelock::run( void )
        {
            this->p->run( this );
        }

}




