 /*
represents the lifecycle of a writelock on a dpapi_opengl1o5_vertexbuffer
this object is returned from a dpapi_opengl1o5_vertexbuffer when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_vertexbuffer
*/

#include "dpapi_opengl1o5_vertexbuffer_writelock.h"
#include "dpapi_opengl1o5_vertexbuffer.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_vertexbuffer_writelock::dpapi_opengl1o5_vertexbuffer_writelock( dpapi_opengl1o5_vertexbuffer *p, dpmutex_writelock *ml ) : dpapi_vertexbuffer_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_vertexbuffer_writelock::~dpapi_opengl1o5_vertexbuffer_writelock( void )
    {

    }

}













