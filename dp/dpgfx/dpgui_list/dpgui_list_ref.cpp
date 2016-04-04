
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpgui_list_ref.h"
#include "dpgui_list.h"

namespace dp
{

    //ctor
    dpgui_list_ref::dpgui_list_ref( dpgui_list *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dptask_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpgui_list_ref::~dpgui_list_ref( void )
    {

    }

}







