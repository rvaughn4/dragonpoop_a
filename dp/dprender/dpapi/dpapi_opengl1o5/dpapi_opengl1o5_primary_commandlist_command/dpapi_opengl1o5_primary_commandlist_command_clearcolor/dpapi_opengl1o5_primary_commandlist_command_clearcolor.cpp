
/*

*/

#include "dpapi_opengl1o5_primary_commandlist_command_clearcolor.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_primary_commandlist_command_clearcolor::dpapi_opengl1o5_primary_commandlist_command_clearcolor( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float r, float g, float b, float a, opengl1o5_lib_functions *gl ) : dpapi_primary_commandlist_command_clearcolor( p, ctxl, r, g, b, a )
    {
        this->gl = gl;
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    //dtor
    dpapi_opengl1o5_primary_commandlist_command_clearcolor::~dpapi_opengl1o5_primary_commandlist_command_clearcolor( void )
    {

    }

    //compile command
    bool dpapi_opengl1o5_primary_commandlist_command_clearcolor::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_opengl1o5_primary_commandlist_command_clearcolor::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        this->gl->glClearColor( this->r, this->g, this->b, this->a );
        this->gl->glClear( opengl1o5_lib_COLOR_BUFFER_BIT );
        return 1;
    }

}
















