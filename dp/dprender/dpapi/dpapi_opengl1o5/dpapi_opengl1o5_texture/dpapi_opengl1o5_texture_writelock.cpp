 /*
represents the lifecycle of a writelock on a dpapi_opengl1o5_texture
this object is returned from a dpapi_opengl1o5_texture when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_texture
*/

#include "dpapi_opengl1o5_texture_writelock.h"
#include "dpapi_opengl1o5_texture.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_texture_writelock::dpapi_opengl1o5_texture_writelock( dpapi_opengl1o5_texture *p, dpmutex_writelock *ml ) : dpapi_texture_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_texture_writelock::~dpapi_opengl1o5_texture_writelock( void )
    {

    }

}












