
/*

*/

#include "dpapi_opengl1o5_factory.h"
#include "dpapi_opengl1o5.h"
#include "../../../dpwindow/dpwindow/dpwindow_factory.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_factory::dpapi_opengl1o5_factory( void )
    {

    }

    //dtor
    dpapi_opengl1o5_factory::~dpapi_opengl1o5_factory( void )
    {

    }

    //creates window
    dpapi *dpapi_opengl1o5_factory::makeApi( void )
    {
        return new dpapi_opengl1o5( new dpwindow_factory() );
    }

    //clones factory
    dpapi_factory *dpapi_opengl1o5_factory::clone( void )
    {
        return new dpapi_opengl1o5_factory();
    }

}








