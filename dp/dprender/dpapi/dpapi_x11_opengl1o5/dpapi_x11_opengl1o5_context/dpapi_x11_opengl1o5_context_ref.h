
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_x11_opengl1o5_context_ref_h
#define dpapi_x11_opengl1o5_context_ref_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5_context/dpapi_opengl1o5_context_ref.h"

namespace dp
{

    class dpapi_x11_opengl1o5_context;

    class dpapi_x11_opengl1o5_context_ref : public dpapi_opengl1o5_context_ref
    {

    private:

        dpapi_x11_opengl1o5_context *p;

    protected:

        //dtor
        virtual ~dpapi_x11_opengl1o5_context_ref( void );

    public:

        //ctor
        dpapi_x11_opengl1o5_context_ref( dpapi_x11_opengl1o5_context *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_x11_opengl1o5_context;
    };

}

#endif








