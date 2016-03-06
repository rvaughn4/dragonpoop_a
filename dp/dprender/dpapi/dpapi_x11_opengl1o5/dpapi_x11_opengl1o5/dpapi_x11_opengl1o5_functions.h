
#ifndef dpapi_x11_opengl1o5_functions_h
#define dpapi_x11_opengl1o5_functions_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5/dpapi_opengl1o5_functions.h"
#include "../../../dpwindow/dpwindow_x11/dpwindow_x11.h"

namespace dp
{

    typedef GLXDrawable opengl1o5_lib_GLXDrawable;
    typedef GLXContext opengl1o5_lib_GLXContext;

    typedef void *(* opengl1o5_lib_functions_glXGetProcAddress )( const opengl1o5_lib_GLubyte *procName );
    typedef void (* opengl1o5_lib_functions_glXSwapBuffers )( x11_window_Display *dpy, opengl1o5_lib_GLXDrawable drawable );
    typedef bool (* opengl1o5_lib_functions_glXMakeCurrent )( x11_window_Display *dpy, opengl1o5_lib_GLXDrawable drawable, opengl1o5_lib_GLXContext ctx );
    typedef opengl1o5_lib_GLXContext (* opengl1o5_lib_functions_glXCreateContext )( x11_window_Display *dpy, x11_window_XVisualInfo *vis, opengl1o5_lib_GLXContext shareList, bool direct );
    typedef void (* opengl1o5_lib_functions_glXDestroyContext )( x11_window_Display *dpy, opengl1o5_lib_GLXContext ctx );


    struct opengl1o5_x11_lib_functions
    {
        opengl1o5_lib_functions gl_1o5;

        opengl1o5_lib_functions_glXGetProcAddress glXGetProcAddress;
        opengl1o5_lib_functions_glXSwapBuffers glXSwapBuffers;
        opengl1o5_lib_functions_glXMakeCurrent glXMakeCurrent;
        opengl1o5_lib_functions_glXCreateContext glXCreateContext;
        opengl1o5_lib_functions_glXDestroyContext glXDestroyContext;
    };

};

#endif

