/*
represents the lifecycle of a writelock on a dpthread
this object is returned from a dpthread when writelocked
deleting this object releases the writelock on the dpthread
*/

#include "dpthread_writelock.h"
#include "dpthread.h"

namespace dp
{

    //ctor
    dpthread_writelock::dpthread_writelock( dpthread *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpthread_writelock::~dpthread_writelock( void )
    {

    }

    //returns true if should run
    bool dpthread_writelock::doRun( void )
    {
        return this->p->doRun();
    }

    //returns true if running
    bool dpthread_writelock::isRunning( void )
    {
        return this->p->isRunning();
    }

}





