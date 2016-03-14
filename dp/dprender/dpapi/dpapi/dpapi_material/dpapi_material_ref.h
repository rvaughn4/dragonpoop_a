
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_material_ref_h
#define dpapi_material_ref_h

#include "../../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dpapi_material;

    class dpapi_material_ref : public dpshared_ref
    {

    private:

        dpapi_material *p;

    protected:

        //dtor
        virtual ~dpapi_material_ref( void );

    public:

        //ctor
        dpapi_material_ref( dpapi_material *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_material;
    };

}

#endif









