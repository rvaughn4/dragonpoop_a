
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_opengl1o5_indexbuffer_ref_h
#define dpapi_opengl1o5_indexbuffer_ref_h

#include "../../dpapi/dpapi_indexbuffer/dpapi_indexbuffer_ref.h"

namespace dp
{

    class dpapi_opengl1o5_indexbuffer;

    class dpapi_opengl1o5_indexbuffer_ref : public dpapi_indexbuffer_ref
    {

    private:

        dpapi_opengl1o5_indexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_indexbuffer_ref( void );

    public:

        //ctor
        dpapi_opengl1o5_indexbuffer_ref( dpapi_opengl1o5_indexbuffer *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_opengl1o5_indexbuffer;
    };

}

#endif












