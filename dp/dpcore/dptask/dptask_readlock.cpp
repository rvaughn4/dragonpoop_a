 /*
represents the lifecycle of a readlock on a dptask
this object is returned from a dptask when readlocked
deleting this object releases the readlock on the dptask
*/

#include "dptask_readlock.h"
#include "dptask.h"

namespace dp
{

    //ctor
    dptask_readlock::dptask_readlock( dptask *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dptask_readlock::~dptask_readlock( void )
    {

    }

}





