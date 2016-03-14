
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpapi_indexbuffer_ref.h"
#include "dpapi_indexbuffer.h"

namespace dp
{

    //ctor
    dpapi_indexbuffer_ref::dpapi_indexbuffer_ref( dpapi_indexbuffer *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpapi_indexbuffer_ref::~dpapi_indexbuffer_ref( void )
    {

    }

}










