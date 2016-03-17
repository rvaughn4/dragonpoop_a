/*
represents the lifecycle of a readlock on a dpshared
this object is returned from a dpshared when readlocked
deleting this object releases the readlock on the dpshared
*/

#include "dpbuffer_shared_readlock.h"
#include "dpbuffer_shared.h"

namespace dp
{

    //ctor
    dpbuffer_shared_readlock::dpbuffer_shared_readlock( dpbuffer_shared *p, dpmutex_readlock *ml ) : dpbuffer_wrapper( p ), dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpbuffer_shared_readlock::~dpbuffer_shared_readlock( void )
    {

    }

}






