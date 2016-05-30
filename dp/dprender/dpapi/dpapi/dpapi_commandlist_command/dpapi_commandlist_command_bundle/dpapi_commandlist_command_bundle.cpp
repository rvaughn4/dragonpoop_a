
/*

*/

#include "dpapi_commandlist_command_bundle.h"
#include "../../dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi_bundle/dpapi_bundle.h"
#include "../../dpapi_bundle/dpapi_bundle_writelock.h"
#include "../../../../../dpcore/dpshared/dpshared_guard.h"

namespace dp
{

    //ctor
    dpapi_commandlist_command_bundle::dpapi_commandlist_command_bundle( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl, dpmatrix *mx, dpapi_bundle *bdle, float opacity ) : dpapi_commandlist_command( p, ctxl )
    {
        this->bdle = ctxl->makeBundle( mx, bdle, opacity );
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
        dpshared_guard g;
        dpapi_bundle_writelock *l;

        l = (dpapi_bundle_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->bdle, 100 );
        if( !l )
            return 0;

        return l->compile( ctxl );
    }

    //execute command
    bool dpapi_commandlist_command_bundle::execute( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl )
    {
        dpshared_guard g;
        dpapi_bundle_writelock *l;

        l = (dpapi_bundle_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->bdle, 100 );
        if( !l )
            return 0;

        return l->execute( ctxl );
    }

    //return internal bundle
    dpapi_bundle *dpapi_commandlist_command_bundle::getBundle( void )
    {
        return this->bdle;
    }

}












