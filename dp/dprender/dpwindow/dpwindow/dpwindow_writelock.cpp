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

    //return width
    unsigned int dpwindow_writelock::getWidth( void )
    {
        return this->p->getWidth();
    }

    //return height
    unsigned int dpwindow_writelock::getHeight( void )
    {
        return this->p->getHeight();
    }

    //show window
    bool dpwindow_writelock::show( void )
    {
        return this->p->show();
    }

    //hide window
    bool dpwindow_writelock::hide( void )
    {
        return this->p->hide();
    }

    //returns true if window is shown
    bool dpwindow_writelock::isShown( void )
    {
        return this->p->isShown();
    }

    //make window fullscreen
    bool dpwindow_writelock::fullscreen( void )
    {
        return this->p->fullscreen();
    }

    //make window windowed
    bool dpwindow_writelock::windowed( void )
    {
        return this->p->windowed();
    }

    //returns true if window is fullscreen
    bool dpwindow_writelock::isFullscreen( void )
    {
        return this->p->isFullscreen();
    }

}







