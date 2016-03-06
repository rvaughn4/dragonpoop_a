/*
represents the lifecycle of a writelock on a dpapi_opengl1o5_context
this object is returned from a dpapi_opengl1o5_context when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_context
*/

#include "dpapi_opengl1o5_context_writelock.h"
#include "dpapi_opengl1o5_context.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_context_writelock::dpapi_opengl1o5_context_writelock( dpapi_opengl1o5_context *p, dpmutex_writelock *ml ) : dpapi_context_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_context_writelock::~dpapi_opengl1o5_context_writelock( void )
    {

    }

}










