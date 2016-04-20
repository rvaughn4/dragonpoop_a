
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpinput_ref.h"
#include "dpinput.h"

namespace dp
{

    //ctor
    dpinput_ref::dpinput_ref( dpinput *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpshared_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpinput_ref::~dpinput_ref( void )
    {

    }

}







