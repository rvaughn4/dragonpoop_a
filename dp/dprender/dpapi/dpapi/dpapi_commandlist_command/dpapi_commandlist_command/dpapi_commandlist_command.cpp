
/*

*/

#include "dpapi_commandlist_command.h"

namespace dp
{

    //ctor
    dpapi_commandlist_command::dpapi_commandlist_command( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {

    }

    //dtor
    dpapi_commandlist_command::~dpapi_commandlist_command( void )
    {

    }

    //compile command
    bool dpapi_commandlist_command::compile( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_commandlist_command::execute( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

}











