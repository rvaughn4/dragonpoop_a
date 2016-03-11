
/*

*/

#include "dpapi_primary_commandlist_command_cleardepth.h"

namespace dp
{

    //ctor
    dpapi_primary_commandlist_command_cleardepth::dpapi_primary_commandlist_command_cleardepth( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float d ) : dpapi_primary_commandlist_command( p, ctxl )
    {

    }

    //dtor
    dpapi_primary_commandlist_command_cleardepth::~dpapi_primary_commandlist_command_cleardepth( void )
    {

    }

    //compile command
    bool dpapi_primary_commandlist_command_cleardepth::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_primary_commandlist_command_cleardepth::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

}












