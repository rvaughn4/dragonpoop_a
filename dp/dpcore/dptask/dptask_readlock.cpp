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

    //returns true if running
    bool dptask_readlock::isRun( void )
    {
        return this->p->isRun();
    }

    //return ms delay
    unsigned int dptask_readlock::getDelay( void )
    {
        return this->p->getDelay();
    }
}





