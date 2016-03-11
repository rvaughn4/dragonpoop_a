
/*

*/

#include "dpapi_opengl1o5_primary_commandlist_command_swapbuffers.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_primary_commandlist_command_swapbuffers::dpapi_opengl1o5_primary_commandlist_command_swapbuffers( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, opengl1o5_lib_functions *gl ) : dpapi_primary_commandlist_command_swapbuffers( p, ctxl )
    {
        this->gl = gl;
    }

    //dtor
    dpapi_opengl1o5_primary_commandlist_command_swapbuffers::~dpapi_opengl1o5_primary_commandlist_command_swapbuffers( void )
    {

    }

    //compile command
    bool dpapi_opengl1o5_primary_commandlist_command_swapbuffers::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_opengl1o5_primary_commandlist_command_swapbuffers::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

}


















