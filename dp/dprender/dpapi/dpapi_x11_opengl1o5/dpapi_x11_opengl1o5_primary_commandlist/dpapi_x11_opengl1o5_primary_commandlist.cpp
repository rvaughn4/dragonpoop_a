
/*

*/

#include "dpapi_x11_opengl1o5_primary_commandlist.h"
#include "../dpapi_x11_opengl1o5_primary_commandlist_command/dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers/dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5_primary_commandlist::dpapi_x11_opengl1o5_primary_commandlist( dpapi_context_writelock *ctxl, opengl1o5_x11_lib_functions *gl ) : dpapi_opengl1o5_primary_commandlist( ctxl, &gl->gl_1o5 )
    {
        this->gl = gl;
    }

    //dtor
    dpapi_x11_opengl1o5_primary_commandlist::~dpapi_x11_opengl1o5_primary_commandlist( void )
    {

    }

    dpapi_primary_commandlist_command *dpapi_x11_opengl1o5_primary_commandlist::genCommandSwapBuffers( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        return new dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers( l, ctxl, this->gl );
    }

}










