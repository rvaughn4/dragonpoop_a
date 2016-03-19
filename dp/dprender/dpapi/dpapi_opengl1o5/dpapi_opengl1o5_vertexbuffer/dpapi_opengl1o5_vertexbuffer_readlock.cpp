 /*
represents the lifecycle of a readlock on a dpapi_opengl1o5_vertexbuffer
this object is returned from a dpapi_opengl1o5_vertexbuffer when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_vertexbuffer
*/

#include "dpapi_opengl1o5_vertexbuffer_readlock.h"
#include "dpapi_opengl1o5_vertexbuffer.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_vertexbuffer_readlock::dpapi_opengl1o5_vertexbuffer_readlock( dpapi_opengl1o5_vertexbuffer *p, dpmutex_readlock *ml ) : dpapi_vertexbuffer_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_vertexbuffer_readlock::~dpapi_opengl1o5_vertexbuffer_readlock( void )
    {

    }

}












