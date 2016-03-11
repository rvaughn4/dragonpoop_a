
/*

*/

#include "dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers.h"
#include "../../dpapi_x11_opengl1o5_context/dpapi_x11_opengl1o5_context_writelock.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers::dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, opengl1o5_x11_lib_functions *gl ) : dpapi_opengl1o5_primary_commandlist_command_swapbuffers( p, ctxl, &gl->gl_1o5 )
    {
        this->gl = gl;
    }

    //dtor
    dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers::~dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers( void )
    {

    }

    //compile command
    bool dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        dpapi_x11_opengl1o5_context_writelock *ctx;

        ctx = (dpapi_x11_opengl1o5_context_writelock *)ctxl;
        this->gl->glXSwapBuffers( ctx->getDisplay(), *ctx->getWindow() );

        return 1;
    }

}


















