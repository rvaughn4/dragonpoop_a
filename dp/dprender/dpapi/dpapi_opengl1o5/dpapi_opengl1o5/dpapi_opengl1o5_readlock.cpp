/*
represents the lifecycle of a readlock on a dpapi
this object is returned from a dpapi when readlocked
deleting this object releases the readlock on the dpapi
*/

#include "dpapi_opengl1o5_readlock.h"
#include "dpapi_opengl1o5.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_readlock::dpapi_opengl1o5_readlock( dpapi_opengl1o5 *p, dpmutex_readlock *ml ) : dpapi_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_readlock::~dpapi_opengl1o5_readlock( void )
    {

    }

}









