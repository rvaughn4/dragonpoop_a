
/*

*/

#include "dpapi_commandlist_command_bundle.h"
#include "../../dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi_bundle/dpapi_bundle.h"

namespace dp
{

    //ctor
    dpapi_commandlist_command_bundle::dpapi_commandlist_command_bundle( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl, dpapi_bundle *bdle ) : dpapi_commandlist_command( p, ctxl )
    {
        this->bdle = ctxl->makeBundle( bdle );
    }

    //dtor
    dpapi_commandlist_command_bundle::~dpapi_commandlist_command_bundle( void )
    {
        if( this->bdle )
            delete this->bdle;
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

    //return internal bundle
    dpapi_bundle *dpapi_commandlist_command_bundle::getBundle( void )
    {
        return this->bdle;
    }

}












