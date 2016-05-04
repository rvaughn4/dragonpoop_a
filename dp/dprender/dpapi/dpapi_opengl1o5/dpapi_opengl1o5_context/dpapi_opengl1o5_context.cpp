
/*

*/

#include "dpapi_opengl1o5_context.h"
#include "dpapi_opengl1o5_context_ref.h"
#include "dpapi_opengl1o5_context_readlock.h"
#include "dpapi_opengl1o5_context_writelock.h"
#include "../dpapi_opengl1o5_primary_commandlist/dpapi_opengl1o5_primary_commandlist.h"
#include "../dpapi_opengl1o5_commandlist/dpapi_opengl1o5_commandlist.h"
#include "../dpapi_opengl1o5_vertexbuffer/dpapi_opengl1o5_vertexbuffer.h"
#include "../dpapi_opengl1o5_indexbuffer/dpapi_opengl1o5_indexbuffer.h"
#include "../dpapi_opengl1o5_bundle/dpapi_opengl1o5_bundle.h"
#include "../dpapi_opengl1o5_texture/dpapi_opengl1o5_texture.h"

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
        return new dpapi_opengl1o5_primary_commandlist( (dpapi_opengl1o5_context_writelock *)l, this->gl );
    }

    //generate secondary commandlist
    dpapi_commandlist *dpapi_opengl1o5_context::makeCommandList( dpapi_context_writelock *l )
    {
        return new dpapi_opengl1o5_commandlist( (dpapi_opengl1o5_context_writelock *)l, this->gl );
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

    //generate bundle
    dpapi_bundle *dpapi_opengl1o5_context::makeBundle( dpapi_context_writelock *ctx, dpmatrix *mx, dpapi_vertexbuffer *vb, dpapi_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1 )
    {
        return new dpapi_opengl1o5_bundle( (dpapi_opengl1o5_context_writelock *)ctx, mx, (dpapi_opengl1o5_vertexbuffer *)vb, (dpapi_opengl1o5_indexbuffer *)ib, m, t0, t1, this->gl );
    }

    //generate bundle
    dpapi_bundle *dpapi_opengl1o5_context::makeBundle( dpapi_context_writelock *ctx, dpmatrix *mx, dpapi_bundle *bdle )
    {
        return new dpapi_opengl1o5_bundle( (dpapi_opengl1o5_context_writelock *)ctx, mx, (dpapi_opengl1o5_bundle *)bdle );
    }

    //generate texture
    dpapi_texture *dpapi_opengl1o5_context::makeTexture( dpapi_context_writelock *l, dpbitmap_32bit_uncompressed *bm )
    {
        return new dpapi_opengl1o5_texture( (dpapi_opengl1o5_context_writelock *)l, bm, this->gl );
    }

}








