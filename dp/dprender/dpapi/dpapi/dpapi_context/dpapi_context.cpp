
/*

*/

#include "dpapi_context.h"
#include "dpapi_context_ref.h"
#include "dpapi_context_readlock.h"
#include "dpapi_context_writelock.h"
#include "../dpapi_renderpass/dpapi_renderpass.h"

namespace dp
{

    //ctor
    dpapi_context::dpapi_context( dpapi_writelock *awl ) : dpshared()
    {

    }

    //dtor
    dpapi_context::~dpapi_context( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_context::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_context_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_context::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_context_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_context::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_context_ref( this, k, t_sync );
    }

    //generate renderpass
    dpapi_renderpass *dpapi_context::makeRenderpass( dpapi_context_writelock *l )
    {
        return new dpapi_renderpass( l );
    }

}







