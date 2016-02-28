/*
represents the lifecycle of a writelock on a dptaskmgr
this object is returned from a dptaskmgr when writelocked
deleting this object releases the writelock on the dptaskmgr
*/

#include "dptaskmgr_writelock.h"
#include "dptaskmgr.h"

namespace dp
{

    //ctor
    dptaskmgr_writelock::dptaskmgr_writelock( dptaskmgr *p, dpmutex_writelock *ml ) : dptask_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dptaskmgr_writelock::~dptaskmgr_writelock( void )
    {

    }

    //add static task
    bool dptaskmgr_writelock::addStaticTask( dptask *t, unsigned int weight )
    {
        return this->p->addStaticTask( t, weight );
    }

    //add static task
    bool dptaskmgr_writelock::addStaticTask( dptask_ref *t, unsigned int weight )
    {
        return this->p->addStaticTask( t, weight );
    }

    //add static task
    bool dptaskmgr_writelock::addStaticTask( dptask_readlock *t, unsigned int weight )
    {
        return this->p->addStaticTask( t, weight );
    }

    //add static task
    bool dptaskmgr_writelock::addStaticTask( dptask_writelock *t, unsigned int weight )
    {
        return this->p->addStaticTask( t, weight );
    }

    //add dynamic task
    bool dptaskmgr_writelock::addDynamicTask( dptask *t )
    {
        return this->p->addDynamicTask( t );
    }

    //add dynamic task
    bool dptaskmgr_writelock::addDynamicTask( dptask_ref *t )
    {
        return this->p->addDynamicTask( t );
    }

    //add dynamic task
    bool dptaskmgr_writelock::addDynamicTask( dptask_readlock *t )
    {
        return this->p->addDynamicTask( t );
    }

    //add dynamic task
    bool dptaskmgr_writelock::addDynamicTask( dptask_writelock *t )
    {
        return this->p->addDynamicTask( t );
    }

}







