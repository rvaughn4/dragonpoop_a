
/*

*/

#include "dpapi_vertexbuffer.h"
#include "dpapi_vertexbuffer_ref.h"
#include "dpapi_vertexbuffer_readlock.h"
#include "dpapi_vertexbuffer_writelock.h"

namespace dp
{

    //ctor
    dpapi_vertexbuffer::dpapi_vertexbuffer( dpapi_context_writelock *ctx, dpvertexbuffer *vb )
    {

    }

    //dtor
    dpapi_vertexbuffer::~dpapi_vertexbuffer( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_vertexbuffer::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_vertexbuffer_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_vertexbuffer::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_vertexbuffer_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_vertexbuffer::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_vertexbuffer_ref( this, k, t_sync );
    }

}










