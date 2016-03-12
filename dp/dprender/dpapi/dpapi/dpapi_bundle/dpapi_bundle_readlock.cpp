 /*
represents the lifecycle of a readlock on a dpapi_bundle
this object is returned from a dpapi_bundle when readlocked
deleting this object releases the readlock on the dpapi_bundle
*/

#include "dpapi_bundle_readlock.h"
#include "dpapi_bundle.h"

namespace dp
{

    //ctor
    dpapi_bundle_readlock::dpapi_bundle_readlock( dpapi_bundle *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_bundle_readlock::~dpapi_bundle_readlock( void )
    {

    }

}









