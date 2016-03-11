/*
represents the lifecycle of a writelock on a dpapi
this object is returned from a dpapi when writelocked
deleting this object releases the writelock on the dpapi
*/

#ifndef dpapi_x11_opengl1o5_writelock_h
#define dpapi_x11_opengl1o5_writelock_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5/dpapi_opengl1o5_writelock.h"
#include "dpapi_x11_opengl1o5.h"

namespace dp
{

    class dpapi_x11_opengl1o5;

    class dpapi_x11_opengl1o5_writelock : public dpapi_opengl1o5_writelock
    {

        dpapi_x11_opengl1o5 *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_x11_opengl1o5_writelock( void );

    public:

        //ctor
        dpapi_x11_opengl1o5_writelock( dpapi_x11_opengl1o5 *p, dpmutex_writelock *ml );
        //return x11 display
        x11_window_Display *getDisplay( void );
        //return x11 window
        x11_window_Window *getWindow( void );
        //return x11 visual
        x11_window_XVisualInfo *getVisual( void );

    };

}

#endif








