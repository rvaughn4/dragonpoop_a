
/*

*/

#include "dpapi_bundle.h"
#include "dpapi_bundle_ref.h"
#include "dpapi_bundle_readlock.h"
#include "dpapi_bundle_writelock.h"

namespace dp
{

    //ctor
    dpapi_bundle::dpapi_bundle( dpapi_context_writelock *ctx )
    {

    }

    //dtor
    dpapi_bundle::~dpapi_bundle( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_bundle::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_bundle_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_bundle::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_bundle_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_bundle::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_bundle_ref( this, k, t_sync );
    }

}








