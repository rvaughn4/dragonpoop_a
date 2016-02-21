
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpthread_ref.h"
#include "dpthread.h"

namespace dp
{

    //ctor
    dpthread_ref::dpthread_ref( dpthread *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpthread_ref::~dpthread_ref( void )
    {

    }

}




