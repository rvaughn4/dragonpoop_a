 /*
represents the lifecycle of a readlock on a dpthread
this object is returned from a dpthread when readlocked
deleting this object releases the readlock on the dpthread
*/

#include "dpthread_readlock.h"
#include "dpthread.h"

namespace dp
{

    //ctor
    dpthread_readlock::dpthread_readlock( dpthread *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpthread_readlock::~dpthread_readlock( void )
    {

    }

}




