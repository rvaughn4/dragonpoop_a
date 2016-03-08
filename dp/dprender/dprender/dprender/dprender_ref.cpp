
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dprender_ref.h"
#include "dprender.h"

namespace dp
{

    //ctor
    dprender_ref::dprender_ref( dprender *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dptask_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dprender_ref::~dprender_ref( void )
    {

    }

}








