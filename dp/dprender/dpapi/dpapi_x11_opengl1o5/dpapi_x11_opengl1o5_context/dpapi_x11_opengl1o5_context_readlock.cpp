/*
represents the lifecycle of a readlock on a dpapi_opengl1o5_context
this object is returned from a dpapi_opengl1o5_context when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_context
*/

#include "dpapi_x11_opengl1o5_context_readlock.h"
#include "dpapi_x11_opengl1o5_context.h"

namespace dp
{

    //ctor
    dpapi_x11_opengl1o5_context_readlock::dpapi_x11_opengl1o5_context_readlock( dpapi_x11_opengl1o5_context *p, dpmutex_readlock *ml ) : dpapi_opengl1o5_context_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_x11_opengl1o5_context_readlock::~dpapi_x11_opengl1o5_context_readlock( void )
    {

    }

}











