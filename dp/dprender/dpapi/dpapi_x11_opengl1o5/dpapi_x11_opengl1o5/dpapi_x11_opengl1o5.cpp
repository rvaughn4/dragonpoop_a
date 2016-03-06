
/*

*/

#include "dpapi_x11_opengl1o5.h"
#include "../../../dpwindow/dpwindow_x11/dpwindow_x11_factory.h"

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
        if( this->dlGl )
            dlclose( this->dlGl );
    }

    //override to load opengl library
    bool dpapi_x11_opengl1o5::loadGL( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al )
    {
        bool r;

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

        return r;
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

}







