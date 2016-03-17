
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpbuffer_shared_ref.h"
#include "dpbuffer_shared.h"

namespace dp
{

    //ctor
    dpbuffer_shared_ref::dpbuffer_shared_ref( dpbuffer_shared *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpbuffer_shared_ref::~dpbuffer_shared_ref( void )
    {

    }

}




