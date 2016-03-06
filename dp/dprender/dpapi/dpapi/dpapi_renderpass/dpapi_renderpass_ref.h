
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_renderpass_ref_h
#define dpapi_renderpass_ref_h

#include "../../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dpapi_renderpass;
    class dpapi_renderpass_readlock;
    class dpapi_renderpass_writelock;

    class dpapi_renderpass_ref : public dpshared_ref
    {

    private:

        dpapi_renderpass *p;

    protected:

        //dtor
        virtual ~dpapi_renderpass_ref( void );

    public:

        //ctor
        dpapi_renderpass_ref( dpapi_renderpass *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_renderpass;
    };

}

#endif








