 /*
represents the lifecycle of a writelock on a dpapi_context
this object is returned from a dpapi_context when writelocked
deleting this object releases the writelock on the dpapi_context
*/

#include "dpapi_context_writelock.h"
#include "dpapi_context.h"

namespace dp
{

    //ctor
    dpapi_context_writelock::dpapi_context_writelock( dpapi_context *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_context_writelock::~dpapi_context_writelock( void )
    {

    }

}









