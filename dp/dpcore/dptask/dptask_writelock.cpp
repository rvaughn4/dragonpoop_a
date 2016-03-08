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

    //return ms delay
    unsigned int dptask_writelock::getDelay( void )
    {
        return this->p->getDelay();
    }

    //set delay
    void dptask_writelock::setDelay( unsigned int ms )
    {
        this->p->setDelay( ms );
    }

    //set thread that owns task
    void dptask_writelock::setOwnerThread( dpthread *t )
    {
        this->p->setOwnerThread( t );
    }

    //set thread that owns task
    void dptask_writelock::setOwnerThread( dpthread_writelock *t )
    {
        this->p->setOwnerThread( t );
    }

    //set thread that owns task
    void dptask_writelock::setOwnerThread( dpthread_ref *t )
    {
        this->p->setOwnerThread( t );
    }

    //set task manager that owns task
    void dptask_writelock::setOwnerTaskManager( dptaskmgr *t )
    {
        this->p->setOwnerTaskManager( t );
    }

    //set task manager that owns task
    void dptask_writelock::setOwnerTaskManager( dptaskmgr_writelock *t )
    {
        this->p->setOwnerTaskManager( t );
    }

    //set task manager that owns task
    void dptask_writelock::setOwnerTaskManager( dptaskmgr_ref *t )
    {
        this->p->setOwnerTaskManager( t );
    }

}






