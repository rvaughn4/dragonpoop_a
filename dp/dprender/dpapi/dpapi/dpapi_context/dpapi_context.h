
/*

*/

#ifndef dpapi_context_h
#define dpapi_context_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dpapi_context_writelock;
    class dpapi_writelock;
    class dpapi_renderpass;
    class dpapi_commandlist;
    class dpapi_primary_commandlist;
    class dpvertexbuffer;
    class dpapi_bundle;
    class dpapi_vertexbuffer;
    class dpapi_indexbuffer;
    class dpapi_material;
    class dpapi_texture;
    class dpapi_indexbuffer;
    class dpindexbuffer;
    class dpapi_texture;
    class dpbitmap_32bit_uncompressed;
    class dpmatrix;

    class dpapi_context : public dpshared
    {

    private:

        unsigned int *w, *h;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //generate renderpass
        virtual dpapi_renderpass *makeRenderpass( dpapi_context_writelock *l );
        //generate primary commandlist
        virtual dpapi_primary_commandlist *makePrimaryCommandList( dpapi_context_writelock *l );
        //generate secondary commandlist
        virtual dpapi_commandlist *makeCommandList( dpapi_context_writelock *l );
        //generate vertex buffer
        virtual dpapi_vertexbuffer *makeVertexBuffer( dpapi_context_writelock *l, dpvertexbuffer *vb );
        //generate bundle
        virtual dpapi_bundle *makeBundle( dpapi_context_writelock *ctx, dpmatrix *mx, dpapi_vertexbuffer *vb, dpapi_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1 );
        //generate bundle
        virtual dpapi_bundle *makeBundle( dpapi_context_writelock *ctx, dpmatrix *mx, dpapi_bundle *bdle, float opacity );
        //generate index buffer
        virtual dpapi_indexbuffer *makeIndexBuffer( dpapi_context_writelock *l, dpindexbuffer *ib );
        //generate texture
        virtual dpapi_texture *makeTexture( dpapi_context_writelock *l, dpbitmap_32bit_uncompressed *bm );
        //return screen width
        virtual unsigned int getWidth( void );
        //return screen height
        virtual unsigned int getHeight( void );

    public:

        //ctor
        dpapi_context( dpapi_writelock *awl );
        //dtor
        virtual ~dpapi_context( void );

        friend class dpapi_context_writelock;
        friend class dpapi_context_readlock;
    };

}

#endif






