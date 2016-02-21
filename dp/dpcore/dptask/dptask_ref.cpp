
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dptask_ref.h"
#include "dptask.h"

namespace dp
{

    //ctor
    dptask_ref::dptask_ref( dptask *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dptask_ref::~dptask_ref( void )
    {

    }

}





