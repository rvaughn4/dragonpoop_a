
/*

*/

#include "dpapi_commandlist_command_bundle.h"

namespace dp
{

    //ctor
    dpapi_commandlist_command_bundle::dpapi_commandlist_command_bundle( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl, dpapi_bundle *bdle ) : dpapi_commandlist_command( p, ctxl )
    {

    }

    //dtor
    dpapi_commandlist_command_bundle::~dpapi_commandlist_command_bundle( void )
    {

    }

    //compile command
    bool dpapi_commandlist_command_bundle::compile( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_commandlist_command_bundle::execute( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

}












