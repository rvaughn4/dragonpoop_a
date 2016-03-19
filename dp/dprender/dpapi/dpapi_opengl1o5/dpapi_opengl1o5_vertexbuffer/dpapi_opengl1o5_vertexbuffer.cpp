
/*

*/

#include "dpapi_opengl1o5_vertexbuffer.h"
#include "dpapi_opengl1o5_vertexbuffer_ref.h"
#include "dpapi_opengl1o5_vertexbuffer_readlock.h"
#include "dpapi_opengl1o5_vertexbuffer_writelock.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_writelock.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_vertexbuffer::dpapi_opengl1o5_vertexbuffer( dpapi_opengl1o5_context_writelock *ctx, dpvertexbuffer *vb ) : dpapi_vertexbuffer( ctx, vb )
    {

    }

    //dtor
    dpapi_opengl1o5_vertexbuffer::~dpapi_opengl1o5_vertexbuffer( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_opengl1o5_vertexbuffer::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_opengl1o5_vertexbuffer_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_opengl1o5_vertexbuffer::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_opengl1o5_vertexbuffer_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_opengl1o5_vertexbuffer::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_opengl1o5_vertexbuffer_ref( this, k, t_sync );
    }

}











