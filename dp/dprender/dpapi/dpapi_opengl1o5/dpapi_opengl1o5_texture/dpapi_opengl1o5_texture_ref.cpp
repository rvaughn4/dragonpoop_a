
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#include "dpapi_opengl1o5_texture_ref.h"
#include "dpapi_opengl1o5_texture.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_texture_ref::dpapi_opengl1o5_texture_ref( dpapi_opengl1o5_texture *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dpapi_texture_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpapi_opengl1o5_texture_ref::~dpapi_opengl1o5_texture_ref( void )
    {

    }

}











