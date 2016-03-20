 /*
represents the lifecycle of a writelock on a dpapi_opengl1o5_indexbuffer
this object is returned from a dpapi_opengl1o5_indexbuffer when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_indexbuffer
*/

#include "dpapi_opengl1o5_indexbuffer_writelock.h"
#include "dpapi_opengl1o5_indexbuffer.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_indexbuffer_writelock::dpapi_opengl1o5_indexbuffer_writelock( dpapi_opengl1o5_indexbuffer *p, dpmutex_writelock *ml ) : dpapi_indexbuffer_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_indexbuffer_writelock::~dpapi_opengl1o5_indexbuffer_writelock( void )
    {

    }

    //return ibo
    unsigned int dpapi_opengl1o5_indexbuffer_writelock::getIBO( void )
    {
        return this->p->getIBO();
    }

    //return vb
    dpindexbuffer *dpapi_opengl1o5_indexbuffer_writelock::getIB( void )
    {
        return this->p->getIB();
    }

}














