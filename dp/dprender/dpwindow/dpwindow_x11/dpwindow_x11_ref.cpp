
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpwindow_x11_ref.h"
#include "dpwindow_x11.h"

namespace dp
{

    //ctor
    dpwindow_x11_ref::dpwindow_x11_ref( dpwindow_x11 *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpwindow_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpwindow_x11_ref::~dpwindow_x11_ref( void )
    {

    }

}







