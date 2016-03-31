 /*
represents the lifecycle of a readlock on a dpapi_opengl1o5_texture
this object is returned from a dpapi_opengl1o5_texture when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_texture
*/

#include "dpapi_opengl1o5_texture_readlock.h"
#include "dpapi_opengl1o5_texture.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_texture_readlock::dpapi_opengl1o5_texture_readlock( dpapi_opengl1o5_texture *p, dpmutex_readlock *ml ) : dpapi_texture_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_texture_readlock::~dpapi_opengl1o5_texture_readlock( void )
    {

    }

}











