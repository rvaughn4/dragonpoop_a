
/*

*/

#include "dpapi_renderpass.h"
#include "dpapi_renderpass_ref.h"
#include "dpapi_renderpass_readlock.h"
#include "dpapi_renderpass_writelock.h"

namespace dp
{

    //ctor
    dpapi_renderpass::dpapi_renderpass( dpapi_context_writelock *awl ) : dpshared()
    {

    }

    //dtor
    dpapi_renderpass::~dpapi_renderpass( void )
    {
        this->unlink();
    }

    //generate readlock
    dpshared_readlock *dpapi_renderpass::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_renderpass_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_renderpass::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_renderpass_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_renderpass::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_renderpass_ref( this, k, t_sync );
    }

}








