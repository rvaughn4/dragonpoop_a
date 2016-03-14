
/*

*/

#include "dpapi_indexbuffer.h"
#include "dpapi_indexbuffer_ref.h"
#include "dpapi_indexbuffer_readlock.h"
#include "dpapi_indexbuffer_writelock.h"

namespace dp
{

    //ctor
    dpapi_indexbuffer::dpapi_indexbuffer( dpapi_context_writelock *ctx )
    {

    }

    //dtor
    dpapi_indexbuffer::~dpapi_indexbuffer( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_indexbuffer::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_indexbuffer_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_indexbuffer::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_indexbuffer_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_indexbuffer::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_indexbuffer_ref( this, k, t_sync );
    }

}









