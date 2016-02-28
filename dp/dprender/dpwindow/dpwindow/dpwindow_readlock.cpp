/*
represents the lifecycle of a readlock on a dpwindow
this object is returned from a dpwindow when readlocked
deleting this object releases the readlock on the dpwindow
*/

#include "dpwindow_readlock.h"
#include "dpwindow.h"

namespace dp
{

    //ctor
    dpwindow_readlock::dpwindow_readlock( dpwindow *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpwindow_readlock::~dpwindow_readlock( void )
    {

    }

}






