
/*

*/

#include "dpapi_x11_opengl1o5_factory.h"
#include "dpapi_x11_opengl1o5.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5_factory::dpapi_x11_opengl1o5_factory( unsigned int w, unsigned int h, const char *cname )
    {
        this->w = w;
        this->h = h;
        this->sname.assign( cname );
    }

    //dtor
    dpapi_x11_opengl1o5_factory::~dpapi_x11_opengl1o5_factory( void )
    {

    }

    //creates window
    dpapi *dpapi_x11_opengl1o5_factory::makeApi( void )
    {
        return new dpapi_x11_opengl1o5( this->w, this->h, this->sname.c_str() );
    }

    //clones factory
    dpapi_factory *dpapi_x11_opengl1o5_factory::clone( void )
    {
        return new dpapi_x11_opengl1o5_factory( this->w, this->h, this->sname.c_str() );
    }

}









