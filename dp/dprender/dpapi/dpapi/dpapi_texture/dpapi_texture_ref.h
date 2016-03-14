
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_texture_ref_h
#define dpapi_texture_ref_h

#include "../../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dpapi_texture;

    class dpapi_texture_ref : public dpshared_ref
    {

    private:

        dpapi_texture *p;

    protected:

        //dtor
        virtual ~dpapi_texture_ref( void );

    public:

        //ctor
        dpapi_texture_ref( dpapi_texture *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_texture;
    };

}

#endif









