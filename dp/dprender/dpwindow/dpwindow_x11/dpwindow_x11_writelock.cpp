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

    //return display
    x11_window_Display *dpwindow_x11_writelock::getDisplay( void )
    {
        return this->p->getDisplay();
    }

    //return window
    x11_window_Window *dpwindow_x11_writelock::getWindow( void )
    {
        return this->p->getWindow();
    }

    //return visual
    x11_window_XVisualInfo *dpwindow_x11_writelock::getVisual( void )
    {
        return this->p->getVisual();
    }

}








