
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpgfx_ref.h"
#include "dpgfx.h"

namespace dp
{

    //ctor
    dpgfx_ref::dpgfx_ref( dpgfx *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dptask_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpgfx_ref::~dpgfx_ref( void )
    {

    }

}







