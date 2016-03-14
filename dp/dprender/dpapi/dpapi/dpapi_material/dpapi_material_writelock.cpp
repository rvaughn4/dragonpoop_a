 /*
represents the lifecycle of a writelock on a dpapi_material
this object is returned from a dpapi_material when writelocked
deleting this object releases the writelock on the dpapi_material
*/

#include "dpapi_material_writelock.h"
#include "dpapi_material.h"

namespace dp
{

    //ctor
    dpapi_material_writelock::dpapi_material_writelock( dpapi_material *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_material_writelock::~dpapi_material_writelock( void )
    {

    }

}











