 /*
represents the lifecycle of a writelock on a dpapi_shader
this object is returned from a dpapi_shader when writelocked
deleting this object releases the writelock on the dpapi_shader
*/

#include "dpapi_shader_writelock.h"
#include "dpapi_shader.h"

namespace dp
{

    //ctor
    dpapi_shader_writelock::dpapi_shader_writelock( dpapi_shader *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_shader_writelock::~dpapi_shader_writelock( void )
    {

    }

}











