
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpthread_ref_h
#define dpthread_ref_h

#include "dpthread_defines.h"
#include "../dpshared/dpshared_ref.h"

namespace dp
{

    class dpthread;
    class dpthread_readlock;
    class dpthread_writelock;

    class dpthread_ref : public dpshared_ref
    {

    private:

        dpthread *p;

    protected:

    public:


        //ctor
        dpthread_ref( dpthread *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //dtor
        virtual ~dpthread_ref( void );

    };

}

#endif



