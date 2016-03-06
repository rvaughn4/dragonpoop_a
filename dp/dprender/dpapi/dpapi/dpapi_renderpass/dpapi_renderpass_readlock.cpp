 /*
represents the lifecycle of a readlock on a dpapi_renderpass
this object is returned from a dpapi_renderpass when readlocked
deleting this object releases the readlock on the dpapi_renderpass
*/

#include "dpapi_renderpass_readlock.h"
#include "dpapi_renderpass.h"

namespace dp
{

    //ctor
    dpapi_renderpass_readlock::dpapi_renderpass_readlock( dpapi_renderpass *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_renderpass_readlock::~dpapi_renderpass_readlock( void )
    {

    }

}











