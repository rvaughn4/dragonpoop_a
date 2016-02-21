
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dptask_ref_h
#define dptask_ref_h

#include "dptask_defines.h"
#include "../dpshared/dpshared_ref.h"

namespace dp
{

    class dptask;
    class dptask_readlock;
    class dptask_writelock;

    class dptask_ref : public dpshared_ref
    {

    private:

        dptask *p;

    protected:

        //dtor
        virtual ~dptask_ref( void );

    public:

        //ctor
        dptask_ref( dptask *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dptask;
    };

}

#endif




