 /*
represents the lifecycle of a readlock on a dpapi_texture
this object is returned from a dpapi_texture when readlocked
deleting this object releases the readlock on the dpapi_texture
*/

#include "dpapi_texture_readlock.h"
#include "dpapi_texture.h"

namespace dp
{

    //ctor
    dpapi_texture_readlock::dpapi_texture_readlock( dpapi_texture *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_texture_readlock::~dpapi_texture_readlock( void )
    {

    }

}










