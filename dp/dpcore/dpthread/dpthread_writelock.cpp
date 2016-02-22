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

    //return thread delay time
    unsigned int dpthread_writelock::getDelay( void )
    {
        return this->p->getDelay();
    }

    //add a static task to task list
    bool dpthread_writelock::addStaticTask( dptask *t, unsigned int weight )
    {
        return this->p->addStaticTask( t, weight );
    }

    //add a static task to task list
    bool dpthread_writelock::addStaticTask( dptask_ref *t, unsigned int weight )
    {
        return this->p->addStaticTask( t, weight );
    }

    //add a static task to task list
    bool dpthread_writelock::addStaticTask( dptask_readlock *t, unsigned int weight )
    {
        return this->p->addStaticTask( t, weight );
    }

    //add a static task to task list
    bool dpthread_writelock::addStaticTask( dptask_writelock *t, unsigned int weight )
    {
        return this->p->addStaticTask( t, weight );
    }

    //add a dynamic task to task list
    bool dpthread_writelock::addDynamicTask( dptask *t )
    {
        return this->p->addDynamicTask( t );
    }

    //add a dynamic task to task list
    bool dpthread_writelock::addDynamicTask( dptask_ref *t )
    {
        return this->p->addDynamicTask( t );
    }

    //add a dynamic task to task list
    bool dpthread_writelock::addDynamicTask( dptask_readlock *t )
    {
        return this->p->addDynamicTask( t );
    }

    //add a dynamic task to task list
    bool dpthread_writelock::addDynamicTask( dptask_writelock *t )
    {
        return this->p->addDynamicTask( t );
    }

}





