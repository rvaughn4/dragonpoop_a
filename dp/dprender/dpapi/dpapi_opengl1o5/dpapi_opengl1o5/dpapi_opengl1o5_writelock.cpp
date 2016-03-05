/*
represents the lifecycle of a writelock on a dpapi
this object is returned from a dpapi when writelocked
deleting this object releases the writelock on the dpapi
*/

#include "dpapi_opengl1o5_writelock.h"
#include "dpapi_opengl1o5.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_writelock::dpapi_opengl1o5_writelock( dpapi_opengl1o5 *p, dpmutex_writelock *ml ) : dpapi_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_writelock::~dpapi_opengl1o5_writelock( void )
    {

    }

}









