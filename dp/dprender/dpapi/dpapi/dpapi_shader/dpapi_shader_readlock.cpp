 /*
represents the lifecycle of a readlock on a dpapi_shader
this object is returned from a dpapi_shader when readlocked
deleting this object releases the readlock on the dpapi_shader
*/

#include "dpapi_shader_readlock.h"
#include "dpapi_shader.h"

namespace dp
{

    //ctor
    dpapi_shader_readlock::dpapi_shader_readlock( dpapi_shader *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_shader_readlock::~dpapi_shader_readlock( void )
    {

    }

}









