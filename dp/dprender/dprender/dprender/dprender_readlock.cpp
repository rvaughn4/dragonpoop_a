/*
represents the lifecycle of a readlock on a dprender
this object is returned from a dprender when readlocked
deleting this object releases the readlock on the dprender
*/

#include "dprender_readlock.h"
#include "dprender.h"

namespace dp
{

    //ctor
    dprender_readlock::dprender_readlock( dprender *p, dpmutex_readlock *ml ) : dptask_readlock( p, ml )
    {

    }

    //dtor
    dprender_readlock::~dprender_readlock( void )
    {

    }

}










