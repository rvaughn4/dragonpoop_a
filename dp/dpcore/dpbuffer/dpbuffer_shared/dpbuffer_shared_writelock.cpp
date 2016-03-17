/*
represents the lifecycle of a writelock on a dpshared
this object is returned from a dpshared when writelocked
deleting this object releases the writelock on the dpshared
*/

#include "dpbuffer_shared_writelock.h"
#include "dpbuffer_shared.h"

namespace dp
{

    //ctor
    dpbuffer_shared_writelock::dpbuffer_shared_writelock( dpbuffer_shared *p, dpmutex_writelock *ml ) : dpbuffer_wrapper( p ), dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpbuffer_shared_writelock::~dpbuffer_shared_writelock( void )
    {

    }

}





