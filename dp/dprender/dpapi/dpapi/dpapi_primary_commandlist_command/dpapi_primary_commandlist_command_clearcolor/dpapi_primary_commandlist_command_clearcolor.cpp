
/*

*/

#include "dpapi_primary_commandlist_command_clearcolor.h"

namespace dp
{

    //ctor
    dpapi_primary_commandlist_command_clearcolor::dpapi_primary_commandlist_command_clearcolor( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float r, float g, float b, float a ) : dpapi_primary_commandlist_command( p, ctxl )
    {

    }

    //dtor
    dpapi_primary_commandlist_command_clearcolor::~dpapi_primary_commandlist_command_clearcolor( void )
    {

    }

    //compile command
    bool dpapi_primary_commandlist_command_clearcolor::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_primary_commandlist_command_clearcolor::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

}











