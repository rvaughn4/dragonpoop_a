/*
represents the lifecycle of a readlock on a dpapi_context
this object is returned from a dpapi_context when readlocked
deleting this object releases the readlock on the dpapi_context
*/

#include "dpapi_context_readlock.h"
#include "dpapi_context.h"

namespace dp
{

    //ctor
    dpapi_context_readlock::dpapi_context_readlock( dpapi_context *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_context_readlock::~dpapi_context_readlock( void )
    {

    }

}








