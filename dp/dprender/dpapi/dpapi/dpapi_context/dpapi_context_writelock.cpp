 /*
represents the lifecycle of a writelock on a dpapi_context
this object is returned from a dpapi_context when writelocked
deleting this object releases the writelock on the dpapi_context
*/

#include "dpapi_context_writelock.h"
#include "dpapi_context.h"

namespace dp
{

    //ctor
    dpapi_context_writelock::dpapi_context_writelock( dpapi_context *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_context_writelock::~dpapi_context_writelock( void )
    {

    }

    //generate renderpass
    dpapi_renderpass *dpapi_context_writelock::makeRenderpass( void )
    {
        return this->p->makeRenderpass( this );
    }

    //generate primary commandlist
    dpapi_primary_commandlist *dpapi_context_writelock::makePrimaryCommandList( void )
    {
        return this->p->makePrimaryCommandList( this );
    }

    //generate secondary commandlist
    dpapi_commandlist *dpapi_context_writelock::makeCommandList( void )
    {
        return this->p->makeCommandList( this );
    }

    //generate vertex buffer
    dpapi_vertexbuffer *dpapi_context_writelock::makeVertexBuffer( dpvertexbuffer *vb )
    {
        return this->p->makeVertexBuffer( this, vb );
    }

    //generate bundle
    dpapi_bundle *dpapi_context_writelock::makeBundle( dpapi_vertexbuffer *vb, dpapi_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1 )
    {
        return this->p->makeBundle( this, vb, ib, m, t0, t1 );
    }

    //generate bundle
    dpapi_bundle *dpapi_context_writelock::makeBundle( dpapi_bundle *bdle )
    {
        return this->p->makeBundle( this, bdle );
    }

    //generate index buffer
    dpapi_indexbuffer *dpapi_context_writelock::makeIndexBuffer( dpindexbuffer *ib )
    {
        return this->p->makeIndexBuffer( this, ib );
    }

    //generate texture
    dpapi_texture *dpapi_context_writelock::makeTexture( dpbitmap *bm )
    {
        return this->p->makeTexture( this, bm );
    }

}









