
/*

*/

#include "dpapi_primary_commandlist_command_swapbuffers.h"

namespace dp
{

    //ctor
    dpapi_primary_commandlist_command_swapbuffers::dpapi_primary_commandlist_command_swapbuffers( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl ) : dpapi_primary_commandlist_command( p, ctxl )
    {

    }

    //dtor
    dpapi_primary_commandlist_command_swapbuffers::~dpapi_primary_commandlist_command_swapbuffers( void )
    {

    }

    //compile command
    bool dpapi_primary_commandlist_command_swapbuffers::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

    //execute command
    bool dpapi_primary_commandlist_command_swapbuffers::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        return 1;
    }

}













