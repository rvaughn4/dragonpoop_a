/*
represents the lifecycle of a readlock on a dpwindow
this object is returned from a dpwindow when readlocked
deleting this object releases the readlock on the dpwindow
*/

#include "dpwindow_x11_readlock.h"
#include "dpwindow_x11.h"

namespace dp
{

    //ctor
    dpwindow_x11_readlock::dpwindow_x11_readlock( dpwindow_x11 *p, dpmutex_readlock *ml ) : dpwindow_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpwindow_x11_readlock::~dpwindow_x11_readlock( void )
    {

    }

}







