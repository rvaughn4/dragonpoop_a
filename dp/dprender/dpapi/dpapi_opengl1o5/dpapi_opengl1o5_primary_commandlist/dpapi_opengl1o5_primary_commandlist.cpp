
/*

*/

#include "dpapi_opengl1o5_primary_commandlist.h"
#include "../dpapi_opengl1o5_primary_commandlist_command/dpapi_opengl1o5_primary_commandlist_command_clearcolor/dpapi_opengl1o5_primary_commandlist_command_clearcolor.h"
#include "../dpapi_opengl1o5_primary_commandlist_command/dpapi_opengl1o5_primary_commandlist_command_cleardepth/dpapi_opengl1o5_primary_commandlist_command_cleardepth.h"
#include "../dpapi_opengl1o5_primary_commandlist_command/dpapi_opengl1o5_primary_commandlist_command_swapbuffers/dpapi_opengl1o5_primary_commandlist_command_swapbuffers.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_primary_commandlist::dpapi_opengl1o5_primary_commandlist( dpapi_context_writelock *ctxl, opengl1o5_lib_functions *gl ) : dpapi_primary_commandlist( ctxl )
    {
        this->gl = gl;
    }

    //dtor
    dpapi_opengl1o5_primary_commandlist::~dpapi_opengl1o5_primary_commandlist( void )
    {

    }

    //generate clear color buffer command
    dpapi_primary_commandlist_command *dpapi_opengl1o5_primary_commandlist::genCommandClearColor( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float r, float g, float b, float a )
    {
        return new dpapi_opengl1o5_primary_commandlist_command_clearcolor( l, ctxl, r, g, b, a, this->gl );
    }

    //generate clear depth buffer command
    dpapi_primary_commandlist_command *dpapi_opengl1o5_primary_commandlist::genCommandClearDepth( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float d )
    {
        return new dpapi_opengl1o5_primary_commandlist_command_cleardepth( l, ctxl, d, this->gl );
    }

    //generate start renderpass command
    dpapi_primary_commandlist_command *dpapi_opengl1o5_primary_commandlist::genCommandRenderpassStart( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_renderpass *rp )
    {
        return 0;
    }

    //generate end renderpass command
    dpapi_primary_commandlist_command *dpapi_opengl1o5_primary_commandlist::genCommandRenderpassEnd( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        return 0;
    }

    //generate swap buffers command
    dpapi_primary_commandlist_command *dpapi_opengl1o5_primary_commandlist::genCommandSwapBuffers( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        return new dpapi_opengl1o5_primary_commandlist_command_swapbuffers( l, ctxl, this->gl );
    }

}










