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

        //returns current epoch time in seconds
        uint64_t dpshared_writelock::getEpoch( void )
        {
            return this->p->getEpoch();
        }

        //returns tickcount in ms
        uint64_t dpshared_writelock::getTicks( void )
        {
            return this->p->getTicks();
        }

        //set shared object to sync by
        void dpshared_writelock::setSync( dpshared *psync )
        {
            this->p->setSync( psync );
        }

        //set shared object to sync by
        void dpshared_writelock::setSync( dpshared_ref *psync )
        {
            this->p->setSync( psync );
        }

        //set shared object to sync by
        void dpshared_writelock::setSync( dpshared_readlock *psync )
        {
            this->p->setSync( psync );
        }

        //set shared object to sync by
        void dpshared_writelock::setSync( dpshared_writelock *psync )
        {
            this->p->setSync( psync );
        }

}




