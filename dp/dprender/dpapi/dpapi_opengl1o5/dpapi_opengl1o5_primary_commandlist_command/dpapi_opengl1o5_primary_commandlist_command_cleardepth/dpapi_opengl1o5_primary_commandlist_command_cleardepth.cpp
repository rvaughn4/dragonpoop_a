
/*

*/

#include "dpapi_opengl1o5_primary_commandlist_command_cleardepth.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_primary_commandlist_command_cleardepth::dpapi_opengl1o5_primary_commandlist_command_cleardepth( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float d, opengl1o5_lib_functions *gl ) : dpapi_primary_commandlist_command_cleardepth( p, ctxl, d )
    {
        this->gl = gl;
        this->d = d;
    }

    //dtor
    dpapi_opengl1o5_primary_commandlist_command_cleardepth::~dpapi_opengl1o5_primary_commandlist_command_cleardepth( void )
    {

    }

    //compile command
    bool dpapi_opengl1o5_primary_commandlist_command_cleardepth::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_opengl1o5_primary_commandlist_command_cleardepth::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        this->gl->glClearDepth( this->d );
        this->gl->glClear( opengl1o5_lib_DEPTH_BUFFER_BIT );
        return 1;
    }

}

















