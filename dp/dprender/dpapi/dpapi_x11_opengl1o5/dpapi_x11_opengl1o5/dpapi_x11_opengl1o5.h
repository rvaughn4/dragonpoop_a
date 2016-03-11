
/*

*/

#ifndef dpapi_x11_opengl1o5_h
#define dpapi_x11_opengl1o5_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5/dpapi_opengl1o5.h"
#include "dpapi_x11_opengl1o5_functions.h"
#include "../../../dpwindow/dpwindow_x11/dpwindow_x11_writelock.h"

namespace dp
{

    #define dpapi_x11_opengl1o5_MAX_CTX 16

    class dpapi_x11_opengl1o5 : public dpapi_opengl1o5
    {

    private:

        opengl1o5_x11_lib_functions gl;
        void *dlGl;
        x11_window_Display *dpy;
        x11_window_Window *win;
        x11_window_XVisualInfo *vi;

        opengl1o5_lib_GLXContext main_ctx;
        unsigned int last_ctx;
        opengl1o5_lib_GLXContext shared_ctx[ dpapi_x11_opengl1o5_MAX_CTX ];

    protected:

        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //override to load opengl library
        virtual bool loadGL( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al );
        //override to handle loading of function pointers
        virtual void *loadFunction( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al, const char *cname );
        //override to provide pointer to gl function pointers
        virtual opengl1o5_lib_functions *getGL( void );
        //return x11 display
        x11_window_Display *getDisplay( void );
        //return x11 window
        x11_window_Window *getWindow( void );
        //return x11 visual
        x11_window_XVisualInfo *getVisual( void );
        //override to generate rendering context
        virtual dpapi_context *makeContext( dpapi_writelock *al );

    public:

        //ctor
        dpapi_x11_opengl1o5( unsigned int w, unsigned int h, const char *cname );
        //dtor
        virtual ~dpapi_x11_opengl1o5( void );

        friend class dpapi_x11_opengl1o5_writelock;

    };

}

#endif






