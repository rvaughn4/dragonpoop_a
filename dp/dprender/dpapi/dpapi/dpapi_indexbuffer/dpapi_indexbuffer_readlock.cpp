 /*
represents the lifecycle of a readlock on a dpapi_indexbuffer
this object is returned from a dpapi_indexbuffer when readlocked
deleting this object releases the readlock on the dpapi_indexbuffer
*/

#include "dpapi_indexbuffer_readlock.h"
#include "dpapi_indexbuffer.h"

namespace dp
{

    //ctor
    dpapi_indexbuffer_readlock::dpapi_indexbuffer_readlock( dpapi_indexbuffer *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_indexbuffer_readlock::~dpapi_indexbuffer_readlock( void )
    {

    }

}










