 /*
represents the lifecycle of a writelock on a dpapi_commandlist
this object is returned from a dpapi_commandlist when writelocked
deleting this object releases the writelock on the dpapi_commandlist
*/

#include "dpapi_commandlist_writelock.h"
#include "dpapi_commandlist.h"

namespace dp
{

    //ctor
    dpapi_commandlist_writelock::dpapi_commandlist_writelock( dpapi_commandlist *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_commandlist_writelock::~dpapi_commandlist_writelock( void )
    {

    }

    //clear and make commandlist ready to accept commands
    bool dpapi_commandlist_writelock::clearAndRecord( dpapi_context_writelock *ctx )
    {
        return this->p->clearAndRecord( ctx, this );
    }

    //compile list
    bool dpapi_commandlist_writelock::compile( dpapi_context_writelock *ctx )
    {
        return this->p->compile( ctx, this );
    }

    //execute list
    bool dpapi_commandlist_writelock::execute( dpapi_context_writelock *ctx )
    {
        return this->p->execute( ctx, this );
    }

    //add bundle to commandlist
    bool dpapi_commandlist_writelock::addBundle( dpapi_context_writelock *ctx, dpmatrix *mx, dpapi_bundle *bdle )
    {
        return this->p->addBundle( ctx, this, mx, bdle );
    }

}










