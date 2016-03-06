
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpapi_commandlist_ref.h"
#include "dpapi_commandlist.h"

namespace dp
{

    //ctor
    dpapi_commandlist_ref::dpapi_commandlist_ref( dpapi_commandlist *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpapi_commandlist_ref::~dpapi_commandlist_ref( void )
    {

    }

}









