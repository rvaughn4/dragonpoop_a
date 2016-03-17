
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpbuffer_shared_ref_h
#define dpbuffer_shared_ref_h

#include "../../dpshared/dpshared_ref.h"

namespace dp
{

    class dpbuffer_shared;

    class dpbuffer_shared_ref : public dpshared_ref
    {

    private:

        dpbuffer_shared *p;

    protected:

        //dtor
        virtual ~dpbuffer_shared_ref( void );

    public:

        //ctor
        dpbuffer_shared_ref( dpbuffer_shared *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpbuffer_shared;
    };

}

#endif



