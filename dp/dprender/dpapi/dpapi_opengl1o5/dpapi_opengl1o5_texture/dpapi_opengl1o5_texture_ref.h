
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_opengl1o5_texture_ref_h
#define dpapi_opengl1o5_texture_ref_h

#include "../../dpapi/dpapi_texture/dpapi_texture_ref.h"

namespace dp
{

    class dpapi_opengl1o5_texture;

    class dpapi_opengl1o5_texture_ref : public dpapi_texture_ref
    {

    private:

        dpapi_opengl1o5_texture *p;

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_texture_ref( void );

    public:

        //ctor
        dpapi_opengl1o5_texture_ref( dpapi_opengl1o5_texture *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_opengl1o5_texture;
    };

}

#endif










