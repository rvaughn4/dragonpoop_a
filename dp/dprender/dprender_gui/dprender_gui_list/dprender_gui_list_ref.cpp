
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dprender_gui_list_ref.h"
#include "dprender_gui_list.h"

namespace dp
{

    //ctor
    dprender_gui_list_ref::dprender_gui_list_ref( dprender_gui_list *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dprender_gui_list_ref::~dprender_gui_list_ref( void )
    {

    }

}








