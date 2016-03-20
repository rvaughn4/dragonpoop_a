 /*
represents the lifecycle of a readlock on a dpapi_opengl1o5_indexbuffer
this object is returned from a dpapi_opengl1o5_indexbuffer when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_indexbuffer
*/

#include "dpapi_opengl1o5_indexbuffer_readlock.h"
#include "dpapi_opengl1o5_indexbuffer.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_indexbuffer_readlock::dpapi_opengl1o5_indexbuffer_readlock( dpapi_opengl1o5_indexbuffer *p, dpmutex_readlock *ml ) : dpapi_indexbuffer_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_indexbuffer_readlock::~dpapi_opengl1o5_indexbuffer_readlock( void )
    {

    }

}













