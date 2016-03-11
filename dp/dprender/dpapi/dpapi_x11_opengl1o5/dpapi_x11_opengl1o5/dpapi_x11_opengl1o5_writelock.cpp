/*
represents the lifecycle of a writelock on a dpapi
this object is returned from a dpapi when writelocked
deleting this object releases the writelock on the dpapi
*/

#include "dpapi_x11_opengl1o5_writelock.h"
#include "dpapi_x11_opengl1o5.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5_writelock::dpapi_x11_opengl1o5_writelock( dpapi_x11_opengl1o5 *p, dpmutex_writelock *ml ) : dpapi_opengl1o5_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_x11_opengl1o5_writelock::~dpapi_x11_opengl1o5_writelock( void )
    {

    }

    //return x11 display
    x11_window_Display *dpapi_x11_opengl1o5_writelock::getDisplay( void )
    {
        return this->p->getDisplay();
    }

    //return x11 window
    x11_window_Window *dpapi_x11_opengl1o5_writelock::getWindow( void )
    {
        return this->p->getWindow();
    }

    //return x11 visual
    x11_window_XVisualInfo *dpapi_x11_opengl1o5_writelock::getVisual( void )
    {
        return this->p->getVisual();
    }

}









