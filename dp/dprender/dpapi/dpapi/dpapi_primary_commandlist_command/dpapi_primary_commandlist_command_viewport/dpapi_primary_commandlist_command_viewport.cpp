
/*

*/

#include "dpapi_primary_commandlist_command_viewport.h"

namespace dp
{

    //ctor
    dpapi_primary_commandlist_command_viewport::dpapi_primary_commandlist_command_viewport( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float x, float y, float w, float h ) : dpapi_primary_commandlist_command( p, ctxl )
    {

    }

    //dtor
    dpapi_primary_commandlist_command_viewport::~dpapi_primary_commandlist_command_viewport( void )
    {

    }

    //compile command
    bool dpapi_primary_commandlist_command_viewport::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_primary_commandlist_command_viewport::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

}













