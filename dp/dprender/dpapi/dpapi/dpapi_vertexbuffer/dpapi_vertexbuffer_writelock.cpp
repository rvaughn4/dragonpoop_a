 /*
represents the lifecycle of a writelock on a dpapi_vertexbuffer
this object is returned from a dpapi_vertexbuffer when writelocked
deleting this object releases the writelock on the dpapi_vertexbuffer
*/

#include "dpapi_vertexbuffer_writelock.h"
#include "dpapi_vertexbuffer.h"

namespace dp
{

    //ctor
    dpapi_vertexbuffer_writelock::dpapi_vertexbuffer_writelock( dpapi_vertexbuffer *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_vertexbuffer_writelock::~dpapi_vertexbuffer_writelock( void )
    {

    }

}












