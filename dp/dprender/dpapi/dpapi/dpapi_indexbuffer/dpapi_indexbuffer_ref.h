
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpapi_indexbuffer_ref_h
#define dpapi_indexbuffer_ref_h

#include "../../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dpapi_indexbuffer;

    class dpapi_indexbuffer_ref : public dpshared_ref
    {

    private:

        dpapi_indexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_indexbuffer_ref( void );

    public:

        //ctor
        dpapi_indexbuffer_ref( dpapi_indexbuffer *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpapi_indexbuffer;
    };

}

#endif









