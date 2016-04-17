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

    //returns true if open
    bool dpwindow_readlock::isOpen( void )
    {
        return this->p->isOpen();
    }

    //return width
    unsigned int dpwindow_readlock::getWidth( void )
    {
        return this->p->getWidth();
    }

    //return height
    unsigned int dpwindow_readlock::getHeight( void )
    {
        return this->p->getHeight();
    }

    //returns true if window is shown
    bool dpwindow_readlock::isShown( void )
    {
        return this->p->isShown();
    }

    //returns true if window is fullscreen
    bool dpwindow_readlock::isFullscreen( void )
    {
        return this->p->isFullscreen();
    }

}






