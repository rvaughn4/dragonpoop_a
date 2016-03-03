
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_context_ref_h
#define dpapi_context_ref_h

#include "../../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dpapi_context;
    class dpapi_context_readlock;
    class dpapi_context_writelock;

    class dpapi_context_ref : public dpshared_ref
    {

    private:

        dpapi_context *p;

    protected:

        //dtor
        virtual ~dpapi_context_ref( void );

    public:

        //ctor
        dpapi_context_ref( dpapi_context *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_context;
    };

}

#endif







