
/*

*/

#include "dpapi_x11_opengl1o5.h"
#include "../../../dpwindow/dpwindow_x11/dpwindow_x11_factory.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5::dpapi_x11_opengl1o5( unsigned int w, unsigned int h, const char *cname ) : dpapi_opengl1o5( new dpwindow_x11_factory( w, h, cname ) )
    {

    }

    //dtor
    dpapi_x11_opengl1o5::~dpapi_x11_opengl1o5( void )
    {

    }

}







