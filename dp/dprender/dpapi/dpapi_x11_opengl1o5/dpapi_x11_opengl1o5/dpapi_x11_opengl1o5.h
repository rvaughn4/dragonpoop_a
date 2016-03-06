
/*

*/

#ifndef dpapi_x11_opengl1o5_h
#define dpapi_x11_opengl1o5_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5/dpapi_opengl1o5.h"
#include "dpapi_x11_opengl1o5_functions.h"

namespace dp
{

    class dpapi_x11_opengl1o5 : public dpapi_opengl1o5
    {

    private:

        opengl1o5_x11_lib_functions gl;
        void *dlGl;

    protected:

        //override to load opengl library
        virtual bool loadGL( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al );
        //override to handle loading of function pointers
        virtual void *loadFunction( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al, const char *cname );
        //override to provide pointer to gl function pointers
        virtual opengl1o5_lib_functions *getGL( void );

    public:

        //ctor
        dpapi_x11_opengl1o5( unsigned int w, unsigned int h, const char *cname );
        //dtor
        virtual ~dpapi_x11_opengl1o5( void );

    };

}

#endif






