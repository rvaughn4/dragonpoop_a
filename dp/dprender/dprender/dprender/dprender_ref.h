
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dprender_ref_h
#define dprender_ref_h

#include "../../../dpcore/dptask/dptask_ref.h"

namespace dp
{

    class dprender;

    class dprender_ref : public dptask_ref
    {

    private:

        dprender *p;

    protected:

        //dtor
        virtual ~dprender_ref( void );

    public:

        //ctor
        dprender_ref( dprender *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dprender;
    };

}

#endif







