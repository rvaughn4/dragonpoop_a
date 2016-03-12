
/*

*/

#include "dpapi_primary_commandlist_command_commandlist.h"
#include "../../dpapi_commandlist/dpapi_commandlist.h"
#include "../../dpapi_commandlist/dpapi_commandlist_ref.h"
#include "../../dpapi_commandlist/dpapi_commandlist_writelock.h"

namespace dp
{

    //ctor
    dpapi_primary_commandlist_command_commandlist::dpapi_primary_commandlist_command_commandlist( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, dpapi_commandlist *cl ) : dpapi_primary_commandlist_command( p, ctxl )
    {
        this->cl = (dpapi_commandlist_ref *)this->gcl.getRef( cl );
    }

    //dtor
    dpapi_primary_commandlist_command_commandlist::~dpapi_primary_commandlist_command_commandlist( void )
    {

    }

    //compile command
    bool dpapi_primary_commandlist_command_commandlist::compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        dpshared_guard g;
        dpapi_commandlist_writelock *l;

        l = (dpapi_commandlist_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->cl, 100 );
        if( !l )
            return 0;

        return l->compile( ctxl );
    }

    //execute command
    bool dpapi_primary_commandlist_command_commandlist::execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        dpshared_guard g;
        dpapi_commandlist_writelock *l;

        l = (dpapi_commandlist_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->cl, 100 );
        if( !l )
            return 0;

        return l->execute( ctxl );
    }

}











