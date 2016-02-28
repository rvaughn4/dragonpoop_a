
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpgfx_ref_h
#define dpgfx_ref_h

#include "../../dpcore/dptask/dptask_ref.h"

namespace dp
{

    class dpgfx;
    class dpgfx_readlock;
    class dpgfx_writelock;

    class dpgfx_ref : public dptask_ref
    {

    private:

        dpgfx *p;

    protected:

        //dtor
        virtual ~dpgfx_ref( void );

    public:

        //ctor
        dpgfx_ref( dpgfx *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpgfx;
    };

}

#endif






