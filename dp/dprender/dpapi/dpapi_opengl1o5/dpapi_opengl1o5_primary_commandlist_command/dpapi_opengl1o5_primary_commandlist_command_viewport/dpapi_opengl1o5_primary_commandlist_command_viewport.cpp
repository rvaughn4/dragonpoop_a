
/*

*/

#include "dpapi_opengl1o5_primary_commandlist_command_viewport.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_primary_commandlist_command_viewport::dpapi_opengl1o5_primary_commandlist_command_viewport( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float x, float y, float w, float h, opengl1o5_lib_functions *gl ) : dpapi_primary_commandlist_command_viewport( p, ctxl, x, y, w, h )
    {
        this->gl = gl;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
    }

    //dtor
    dpapi_opengl1o5_primary_commandlist_command_viewport::~dpapi_opengl1o5_primary_commandlist_command_viewport( void )
    {

    }

    //compile command
    bool dpapi_opengl1o5_primary_commandlist_command_viewport::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_opengl1o5_primary_commandlist_command_viewport::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        this->gl->glViewport( this->x, this->y, this->w, this->h );
        return 1;
    }

}


















