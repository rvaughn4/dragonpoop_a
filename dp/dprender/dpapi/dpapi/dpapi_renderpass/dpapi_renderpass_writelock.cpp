 /*
represents the lifecycle of a writelock on a dpapi_renderpass
this object is returned from a dpapi_renderpass when writelocked
deleting this object releases the writelock on the dpapi_renderpass
*/

#include "dpapi_renderpass_writelock.h"
#include "dpapi_renderpass.h"

namespace dp
{

    //ctor
    dpapi_renderpass_writelock::dpapi_renderpass_writelock( dpapi_renderpass *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_renderpass_writelock::~dpapi_renderpass_writelock( void )
    {

    }

}










