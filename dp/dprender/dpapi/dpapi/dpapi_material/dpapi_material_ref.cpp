
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpapi_material_ref.h"
#include "dpapi_material.h"

namespace dp
{

    //ctor
    dpapi_material_ref::dpapi_material_ref( dpapi_material *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpapi_material_ref::~dpapi_material_ref( void )
    {

    }

}










