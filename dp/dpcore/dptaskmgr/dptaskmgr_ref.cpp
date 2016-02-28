
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dptaskmgr_ref.h"
#include "dptaskmgr.h"

namespace dp
{

    //ctor
    dptaskmgr_ref::dptaskmgr_ref( dptaskmgr *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dptask_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dptaskmgr_ref::~dptaskmgr_ref( void )
    {

    }

}






