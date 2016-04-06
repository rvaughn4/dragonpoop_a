
/*
*/

#include "dpscene_ref.h"
#include "dpscene.h"

namespace dp
{

    //ctor
    dpscene_ref::dpscene_ref( dpscene *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync ) : dptask_ref( p, k, t_sync )
    {
        this->p = p;
    }

    //dtor
    dpscene_ref::~dpscene_ref( void )
    {

    }

}






