 /*
represents the lifecycle of a readlock on a dpapi_vertexbuffer
this object is returned from a dpapi_vertexbuffer when readlocked
deleting this object releases the readlock on the dpapi_vertexbuffer
*/

#include "dpapi_vertexbuffer_readlock.h"
#include "dpapi_vertexbuffer.h"

namespace dp
{

    //ctor
    dpapi_vertexbuffer_readlock::dpapi_vertexbuffer_readlock( dpapi_vertexbuffer *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_vertexbuffer_readlock::~dpapi_vertexbuffer_readlock( void )
    {

    }

}











