/*
represents the lifecycle of a writelock on a dpwindow
this object is returned from a dpwindow when writelocked
deleting this object releases the writelock on the dpwindow
*/

#include "dpwindow_x11_writelock.h"
#include "dpwindow_x11.h"

namespace dp
{

    //ctor
    dpwindow_x11_writelock::dpwindow_x11_writelock( dpwindow_x11 *p, dpmutex_writelock *ml ) : dpwindow_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpwindow_x11_writelock::~dpwindow_x11_writelock( void )
    {

    }

}








