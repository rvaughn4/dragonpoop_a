/*
represents the lifecycle of a writelock on a dpwindow
this object is returned from a dpwindow when writelocked
deleting this object releases the writelock on the dpwindow
*/

#include "dpwindow_writelock.h"
#include "dpwindow.h"

namespace dp
{

    //ctor
    dpwindow_writelock::dpwindow_writelock( dpwindow *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpwindow_writelock::~dpwindow_writelock( void )
    {

    }

    //returns true if open
    bool dpwindow_writelock::isOpen( void )
    {
        return this->p->isOpen();
    }

}







