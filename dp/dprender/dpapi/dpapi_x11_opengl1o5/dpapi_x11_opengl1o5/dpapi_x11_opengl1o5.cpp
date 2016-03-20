
/*

*/

#include "dpapi_x11_opengl1o5.h"
#include "dpapi_x11_opengl1o5_writelock.h"
#include "../../../dpwindow/dpwindow_x11/dpwindow_x11_factory.h"
#include "../dpapi_x11_opengl1o5_context/dpapi_x11_opengl1o5_context.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5::dpapi_x11_opengl1o5( unsigned int w, unsigned int h, const char *cname ) : dpapi_opengl1o5( new dpwindow_x11_factory( w, h, cname ) )
    {
        this->dlGl = 0;
    }

    //dtor
    dpapi_x11_opengl1o5::~dpapi_x11_opengl1o5( void )
    {
        this->unlink();
        if( this->dlGl )
            dlclose( this->dlGl );
    }

    //generate writelock
    dpshared_writelock *dpapi_x11_opengl1o5::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_x11_opengl1o5_writelock( this, ml );
    }

    //override to load opengl library
    bool dpapi_x11_opengl1o5::loadGL( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al )
    {
        bool r;
        dpwindow_x11_writelock *xwl;
        int i;

        xwl = (dpwindow_x11_writelock *)wl;
        this->dpy = xwl->getDisplay();
        this->vi = xwl->getVisual();
        this->win = xwl->getWindow();

        this->dlGl = dlopen( "libGL.so", RTLD_LAZY | RTLD_LOCAL );
        if( !this->dlGl )
            return 0;

        this->gl.glXGetProcAddress = 0;

        r = 1;
        r &= ( this->gl.glXGetProcAddress = (opengl1o5_lib_functions_glXGetProcAddress)this->loadFunction( wl, al, "glXGetProcAddress" ) ) != 0;
        r &= ( this->gl.glXSwapBuffers = (opengl1o5_lib_functions_glXSwapBuffers)this->loadFunction( wl, al, "glXSwapBuffers" ) ) != 0;
        r &= ( this->gl.glXMakeCurrent = (opengl1o5_lib_functions_glXMakeCurrent)this->loadFunction( wl, al, "glXMakeCurrent" ) ) != 0;
        r &= ( this->gl.glXCreateContext = (opengl1o5_lib_functions_glXCreateContext)this->loadFunction( wl, al, "glXCreateContext" ) ) != 0;
        r &= ( this->gl.glXDestroyContext = (opengl1o5_lib_functions_glXDestroyContext)this->loadFunction( wl, al, "glXDestroyContext" ) ) != 0;

        if( !r )
            return 0;

        this->last_ctx = 0;
        this->main_ctx = this->gl.glXCreateContext( this->dpy, this->vi, 0, GL_TRUE );
        if( !this->main_ctx )
            return 0;
        for( i = 0; i < dpapi_x11_opengl1o5_MAX_CTX; i++ )
            this->shared_ctx[ i ] = this->gl.glXCreateContext( this->dpy, this->vi, this->main_ctx, GL_TRUE );

        this->gl.glXMakeCurrent( this->dpy, *this->win, this->main_ctx );

        return 1;
    }

    //override to handle loading of function pointers
    void *dpapi_x11_opengl1o5::loadFunction( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al, const char *cname )
    {
        void *r;

        if( !this->dlGl )
            return 0;

        if( this->gl.glXGetProcAddress )
        {
            r = this->gl.glXGetProcAddress( (const unsigned char *)cname );
            if( r )
                return r;
        }

        r = dlsym( this->dlGl, cname );
        return r;
    }

    //override to provide pointer to gl function pointers
    opengl1o5_lib_functions *dpapi_x11_opengl1o5::getGL( void )
    {
        return (opengl1o5_lib_functions *)&this->gl;
    }

    //return x11 display
    x11_window_Display *dpapi_x11_opengl1o5::getDisplay( void )
    {
        return this->dpy;
    }

    //return x11 window
    x11_window_Window *dpapi_x11_opengl1o5::getWindow( void )
    {
        return this->win;
    }

    //return x11 visual
    x11_window_XVisualInfo *dpapi_x11_opengl1o5::getVisual( void )
    {
        return this->vi;
    }

    //override to generate rendering context
    dpapi_context *dpapi_x11_opengl1o5::makeContext( dpapi_writelock *al )
    {
        dpapi_context *r;

        if( this->last_ctx >= dpapi_x11_opengl1o5_MAX_CTX )
            return 0;
        if( !this->shared_ctx[ this->last_ctx ] )
            return 0;

        r = new dpapi_x11_opengl1o5_context( al, &this->gl, &this->shared_ctx[ this->last_ctx ] );

        if( r )
            this->last_ctx++;
        return r;
    }

}







