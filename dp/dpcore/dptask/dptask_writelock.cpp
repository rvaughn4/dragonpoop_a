/*
represents the lifecycle of a writelock on a dptask
this object is returned from a dptask when writelocked
deleting this object releases the writelock on the dptask
*/

#include "dptask_writelock.h"
#include "dptask.h"

namespace dp
{

    //ctor
    dptask_writelock::dptask_writelock( dptask *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dptask_writelock::~dptask_writelock( void )
    {

    }

    //run task
    void dptask_writelock::run( dpthread_writelock *thdl )
    {
        this->p->run( thdl, this );
    }

    //returns true if running
    bool dptask_writelock::isRun( void )
    {
        return this->p->isRun();
    }

    //stops task
    void dptask_writelock::stop( void )
    {
        this->p->stop();
    }

}






