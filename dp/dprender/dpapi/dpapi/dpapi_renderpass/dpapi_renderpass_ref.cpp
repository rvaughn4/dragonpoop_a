
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpapi_renderpass_ref.h"
#include "dpapi_renderpass.h"

namespace dp
{

    //ctor
    dpapi_renderpass_ref::dpapi_renderpass_ref( dpapi_renderpass *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpapi_renderpass_ref::~dpapi_renderpass_ref( void )
    {

    }

}









