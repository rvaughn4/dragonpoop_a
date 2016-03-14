 /*
represents the lifecycle of a writelock on a dpapi_texture
this object is returned from a dpapi_texture when writelocked
deleting this object releases the writelock on the dpapi_texture
*/

#include "dpapi_texture_writelock.h"
#include "dpapi_texture.h"

namespace dp
{

    //ctor
    dpapi_texture_writelock::dpapi_texture_writelock( dpapi_texture *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_texture_writelock::~dpapi_texture_writelock( void )
    {

    }

}











