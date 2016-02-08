/*
represents the lifecycle of a writelock on a mutex
this object is returned from a mutex when writelocked
deleting this object releases the writelock on the mutex
*/

#include "dpmutex_writelock.h"
#include "dpmutex.h"

namespace dp
{

        //ctor
        dpmutex_writelock::dpmutex_writelock(
                         dpmutex *m
#ifdef dpmutex_debug
                                        ,
                                        const char *cfile_macro,
                                        unsigned int line_macro,
                                        const char *cfunc_macro
#endif
                          )
        {
            this->m = m;
#ifdef dpmutex_debug
            this->cfile_macro = cfile_macro;
            this->line_macro = line_macro;
            this->cfunc_macro = cfunc_macro;
#endif
        }

        //dtor
        dpmutex_writelock::~dpmutex_writelock( void )
        {
#ifdef dpmutex_debug
            this->m->unlock( this, this->cfile_macro, this->line_macro, this->cfunc_macro );
#else
            this->m->unlock( this );
#endif
        }

}



