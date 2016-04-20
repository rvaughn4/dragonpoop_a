
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpwindow_ref.h"
#include "dpwindow.h"

namespace dp
{

    //ctor
    dpwindow_ref::dpwindow_ref( dpwindow *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpinput_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpwindow_ref::~dpwindow_ref( void )
    {

    }

}






