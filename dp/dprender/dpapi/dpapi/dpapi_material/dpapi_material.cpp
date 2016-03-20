
/*

*/

#include "dpapi_material.h"
#include "dpapi_material_ref.h"
#include "dpapi_material_readlock.h"
#include "dpapi_material_writelock.h"

namespace dp
{

    //ctor
    dpapi_material::dpapi_material( dpapi_context_writelock *ctx )
    {

    }

    //dtor
    dpapi_material::~dpapi_material( void )
    {
        this->unlink();
    }

    //generate readlock
    dpshared_readlock *dpapi_material::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_material_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_material::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_material_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_material::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_material_ref( this, k, t_sync );
    }

}









