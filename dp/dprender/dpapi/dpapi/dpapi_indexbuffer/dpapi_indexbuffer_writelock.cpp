 /*
represents the lifecycle of a writelock on a dpapi_indexbuffer
this object is returned from a dpapi_indexbuffer when writelocked
deleting this object releases the writelock on the dpapi_indexbuffer
*/

#include "dpapi_indexbuffer_writelock.h"
#include "dpapi_indexbuffer.h"

namespace dp
{

    //ctor
    dpapi_indexbuffer_writelock::dpapi_indexbuffer_writelock( dpapi_indexbuffer *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_indexbuffer_writelock::~dpapi_indexbuffer_writelock( void )
    {

    }

}











