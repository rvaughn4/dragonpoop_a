
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dptaskmgr_ref_h
#define dptaskmgr_ref_h

#include "../dptask/dptask_ref.h"

namespace dp
{

    class dptaskmgr;
    class dptaskmgr_readlock;
    class dptaskmgr_writelock;

    class dptaskmgr_ref : public dptask_ref
    {

    private:

        dptaskmgr *p;

    protected:

        //dtor
        virtual ~dptaskmgr_ref( void );

    public:

        //ctor
        dptaskmgr_ref( dptaskmgr *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dptaskmgr;
    };

}

#endif





