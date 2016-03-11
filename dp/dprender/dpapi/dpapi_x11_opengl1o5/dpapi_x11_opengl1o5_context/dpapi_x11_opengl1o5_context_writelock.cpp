/*
represents the lifecycle of a writelock on a dpapi_opengl1o5_context
this object is returned from a dpapi_opengl1o5_context when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_context
*/

#include "dpapi_x11_opengl1o5_context_writelock.h"
#include "dpapi_x11_opengl1o5_context.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5_context_writelock::dpapi_x11_opengl1o5_context_writelock( dpapi_x11_opengl1o5_context *p, dpmutex_writelock *ml ) : dpapi_opengl1o5_context_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_x11_opengl1o5_context_writelock::~dpapi_x11_opengl1o5_context_writelock( void )
    {

    }

    //return x11 display
    x11_window_Display *dpapi_x11_opengl1o5_context_writelock::getDisplay( void )
    {
        return this->p->getDisplay();
    }

    //return x11 window
    x11_window_Window *dpapi_x11_opengl1o5_context_writelock::getWindow( void )
    {
        return this->p->getWindow();
    }

    //return x11 visual
    x11_window_XVisualInfo *dpapi_x11_opengl1o5_context_writelock::getVisual( void )
    {
        return this->p->getVisual();
    }

    //return x11 context
    opengl1o5_lib_GLXContext *dpapi_x11_opengl1o5_context_writelock::getContext( void )
    {
        return this->p->getContext();
    }

}










