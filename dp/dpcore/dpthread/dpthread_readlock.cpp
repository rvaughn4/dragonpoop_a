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

    //returns true if should run
    bool dpthread_readlock::doRun( void )
    {
        return this->p->doRun();
    }

    //returns true if running
    bool dpthread_readlock::isRunning( void )
    {
        return this->p->isRunning();
    }

    //return thread delay time
    unsigned int dpthread_readlock::getDelay( void )
    {
        return this->p->getDelay();
    }

}




