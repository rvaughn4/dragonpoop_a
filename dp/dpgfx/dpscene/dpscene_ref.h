
/*
*/

#ifndef dpscene_ref_h
#define dpscene_ref_h

#include "../../dpcore/dptask/dptask_ref.h"

namespace dp
{

    class dpscene;

    class dpscene_ref : public dptask_ref
    {

    private:

        dpscene *p;

    protected:

        //dtor
        virtual ~dpscene_ref( void );

    public:

        //ctor
        dpscene_ref( dpscene *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpscene;
    };

}

#endif





