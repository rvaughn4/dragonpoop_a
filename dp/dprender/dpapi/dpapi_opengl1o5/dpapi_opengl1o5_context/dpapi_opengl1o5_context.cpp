
/*

*/

#include "dpapi_opengl1o5_context.h"
#include "dpapi_opengl1o5_context_ref.h"
#include "dpapi_opengl1o5_context_readlock.h"
#include "dpapi_opengl1o5_context_writelock.h"
#include "../dpapi_opengl1o5_primary_commandlist/dpapi_opengl1o5_primary_commandlist.h"
#include "../dpapi_opengl1o5_vertexbuffer/dpapi_opengl1o5_vertexbuffer.h"
#include "../dpapi_opengl1o5_indexbuffer/dpapi_opengl1o5_indexbuffer.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_context::dpapi_opengl1o5_context( dpapi_writelock *awl, opengl1o5_lib_functions *gl ) : dpapi_context( awl )
    {
        this->gl = gl;
    }

    //dtor
    dpapi_opengl1o5_context::~dpapi_opengl1o5_context( void )
    {
        this->unlink();
    }

    //generate readlock
    dpshared_readlock *dpapi_opengl1o5_context::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_opengl1o5_context_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_opengl1o5_context::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_opengl1o5_context_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_opengl1o5_context::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_opengl1o5_context_ref( this, k, t_sync );
    }

    //generate renderpass
    dpapi_renderpass *dpapi_opengl1o5_context::makeRenderpass( dpapi_opengl1o5_context_writelock *l )
    {
        return 0;
    }

    //generate primary commandlist
    dpapi_primary_commandlist *dpapi_opengl1o5_context::makePrimaryCommandList( dpapi_context_writelock *l )
    {
        return new dpapi_opengl1o5_primary_commandlist( l, this->gl );
    }

    //generate vertex buffer
    dpapi_vertexbuffer *dpapi_opengl1o5_context::makeVertexBuffer( dpapi_context_writelock *l, dpvertexbuffer *vb )
    {
        return new dpapi_opengl1o5_vertexbuffer( (dpapi_opengl1o5_context_writelock *)l, vb, this->gl );
    }

    //make this context active in this thread
    bool dpapi_opengl1o5_context::makeActive( dpapi_opengl1o5_context_writelock *l )
    {
        return 0;
    }

    //generate vertex buffer
    dpapi_indexbuffer *dpapi_opengl1o5_context::makeIndexBuffer( dpapi_context_writelock *l, dpindexbuffer *ib )
    {
        return new dpapi_opengl1o5_indexbuffer( (dpapi_opengl1o5_context_writelock *)l, ib, this->gl );
    }

}








