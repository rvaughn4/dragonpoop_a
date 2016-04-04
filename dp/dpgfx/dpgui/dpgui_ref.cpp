
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpgui_ref.h"
#include "dpgui.h"

namespace dp
{

    //ctor
    dpgui_ref::dpgui_ref( dpgui *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpgui_list_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpgui_ref::~dpgui_ref( void )
    {

    }

}






