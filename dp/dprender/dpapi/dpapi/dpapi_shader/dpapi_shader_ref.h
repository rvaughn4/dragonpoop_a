
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_shader_ref_h
#define dpapi_shader_ref_h

#include "../../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dpapi_shader;

    class dpapi_shader_ref : public dpshared_ref
    {

    private:

        dpapi_shader *p;

    protected:

        //dtor
        virtual ~dpapi_shader_ref( void );

    public:

        //ctor
        dpapi_shader_ref( dpapi_shader *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_shader;
    };

}

#endif









