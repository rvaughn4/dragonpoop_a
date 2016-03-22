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

    //return vbo
    unsigned int dpapi_opengl1o5_vertexbuffer_writelock::getVBO( void )
    {
        return this->p->getVBO();
    }

    //return vb
    dpvertexbuffer *dpapi_opengl1o5_vertexbuffer_writelock::getVB( void )
    {
        return this->p->getVB();
    }

    //return count
    unsigned int dpapi_opengl1o5_vertexbuffer_writelock::getCount( void )
    {
        return this->p->getCount();
    }

}













