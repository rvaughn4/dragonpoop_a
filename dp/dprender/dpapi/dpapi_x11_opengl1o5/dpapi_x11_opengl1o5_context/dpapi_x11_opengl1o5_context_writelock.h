/*
represents the lifecycle of a writelock on a dpapi_opengl1o5_context
this object is returned from a dpapi_opengl1o5_context when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_context
*/

#ifndef dpapi_x11_opengl1o5_context_writelock_h
#define dpapi_x11_opengl1o5_context_writelock_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5_context/dpapi_opengl1o5_context_writelock.h"
#include "dpapi_x11_opengl1o5_context.h"

namespace dp
{

    class dpapi_x11_opengl1o5_context;
    class dpapi_x11_opengl1o5_context_ref;

    class dpapi_x11_opengl1o5_context_writelock : public dpapi_opengl1o5_context_writelock
    {

        dpapi_x11_opengl1o5_context *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_x11_opengl1o5_context_writelock( void );

    public:

        //ctor
        dpapi_x11_opengl1o5_context_writelock( dpapi_x11_opengl1o5_context *p, dpmutex_writelock *ml );
        //return x11 display
        x11_window_Display *getDisplay( void );
        //return x11 window
        x11_window_Window *getWindow( void );
        //return x11 visual
        x11_window_XVisualInfo *getVisual( void );
        //return x11 context
        opengl1o5_lib_GLXContext *getContext( void );

    };

}

#endif









