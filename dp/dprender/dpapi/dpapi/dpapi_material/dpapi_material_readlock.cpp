 /*
represents the lifecycle of a readlock on a dpapi_material
this object is returned from a dpapi_material when readlocked
deleting this object releases the readlock on the dpapi_material
*/

#include "dpapi_material_readlock.h"
#include "dpapi_material.h"

namespace dp
{

    //ctor
    dpapi_material_readlock::dpapi_material_readlock( dpapi_material *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_material_readlock::~dpapi_material_readlock( void )
    {

    }

}










