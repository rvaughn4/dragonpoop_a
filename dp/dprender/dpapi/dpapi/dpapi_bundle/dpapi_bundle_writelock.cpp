 /*
represents the lifecycle of a writelock on a dpapi_bundle
this object is returned from a dpapi_bundle when writelocked
deleting this object releases the writelock on the dpapi_bundle
*/

#include "dpapi_bundle_writelock.h"
#include "dpapi_bundle.h"

namespace dp
{

    //ctor
    dpapi_bundle_writelock::dpapi_bundle_writelock( dpapi_bundle *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_bundle_writelock::~dpapi_bundle_writelock( void )
    {

    }

    //compile bundle
    bool dpapi_bundle_writelock::compile( dpapi_context_writelock *ctx )
    {
        return this->p->compile( ctx, this );
    }

    //execute bundle
    bool dpapi_bundle_writelock::execute( dpapi_context_writelock *ctx )
    {
        return this->p->execute( ctx, this );
    }

}










