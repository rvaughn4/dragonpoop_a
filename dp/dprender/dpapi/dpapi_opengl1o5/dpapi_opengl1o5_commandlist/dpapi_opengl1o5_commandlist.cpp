
/*

*/

#include "dpapi_opengl1o5_commandlist.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_writelock.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_commandlist::dpapi_opengl1o5_commandlist( dpapi_opengl1o5_context_writelock *ctxl, opengl1o5_lib_functions *gl ) : dpapi_commandlist( ctxl )
    {
        this->gl = gl;
    }

    //dtor
    dpapi_opengl1o5_commandlist::~dpapi_opengl1o5_commandlist( void )
    {

    }

}









