
/*

*/

#include "dpapi_context.h"
#include "dpapi_context_ref.h"
#include "dpapi_context_readlock.h"
#include "dpapi_context_writelock.h"
#include "../dpapi_renderpass/dpapi_renderpass.h"
#include "../dpapi_commandlist/dpapi_commandlist.h"
#include "../dpapi_primary_commandlist/dpapi_primary_commandlist.h"
#include "../dpapi_vertexbuffer/dpapi_vertexbuffer.h"
#include "../dpapi_bundle/dpapi_bundle.h"
#include "../dpapi_indexbuffer/dpapi_indexbuffer.h"
#include "../dpapi_texture/dpapi_texture.h"
#include "../dpapi/dpapi_writelock.h"

namespace dp
{

    //ctor
    dpapi_context::dpapi_context( dpapi_writelock *awl ) : dpshared()
    {
        this->w = this->h = (unsigned int *)this;
        awl->getDimensions( &this->w, &this->h );
    }

    //dtor
    dpapi_context::~dpapi_context( void )
    {
        this->unlink();
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

    //generate primary commandlist
    dpapi_primary_commandlist *dpapi_context::makePrimaryCommandList( dpapi_context_writelock *l )
    {
        return new dpapi_primary_commandlist( l );
    }

    //generate secondary commandlist
    dpapi_commandlist *dpapi_context::makeCommandList( dpapi_context_writelock *l )
    {
        return new dpapi_commandlist( l );
    }

    //generate vertex buffer
    dpapi_vertexbuffer *dpapi_context::makeVertexBuffer( dpapi_context_writelock *l, dpvertexbuffer *vb )
    {
        return new dpapi_vertexbuffer( l, vb );
    }

    //generate bundle
    dpapi_bundle *dpapi_context::makeBundle( dpapi_context_writelock *ctx, dpmatrix *mx, dpapi_vertexbuffer *vb, dpapi_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1 )
    {
        return new dpapi_bundle( ctx, mx, vb, ib, m, t0, t1 );
    }

    //generate bundle
    dpapi_bundle *dpapi_context::makeBundle( dpapi_context_writelock *ctx, dpmatrix *mx, dpapi_bundle *bdle )
    {
        return new dpapi_bundle( ctx, mx, bdle );
    }

    //generate index buffer
    dpapi_indexbuffer *dpapi_context::makeIndexBuffer( dpapi_context_writelock *l, dpindexbuffer *ib )
    {
        return new dpapi_indexbuffer( l, ib );
    }

    //generate texture
    dpapi_texture *dpapi_context::makeTexture( dpapi_context_writelock *l, dpbitmap_32bit_uncompressed *bm )
    {
        return new dpapi_texture( l, bm );
    }

    //return screen width
    unsigned int dpapi_context::getWidth( void )
    {
        return *this->w;
    }

    //return screen height
    unsigned int dpapi_context::getHeight( void )
    {
        return *this->h;
    }

}







