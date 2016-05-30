 /*
represents the lifecycle of a writelock on a dpapi_context
this object is returned from a dpapi_context when writelocked
deleting this object releases the writelock on the dpapi_context
*/

#ifndef dpapi_context_writelock_h
#define dpapi_context_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_context;
    class dpmutex_writelock;
    class dpapi_context_ref;
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

    class dpapi_context_writelock : public dpshared_writelock
    {

    private:

        dpapi_context *p;

    protected:

        //dtor
        virtual ~dpapi_context_writelock( void );

    public:

        //ctor
        dpapi_context_writelock( dpapi_context *p, dpmutex_writelock *ml );
        //generate renderpass
        dpapi_renderpass *makeRenderpass( void );
        //generate primary commandlist
        dpapi_primary_commandlist *makePrimaryCommandList( void );
        //generate secondary commandlist
        dpapi_commandlist *makeCommandList( void );
        //generate vertex buffer
        dpapi_vertexbuffer *makeVertexBuffer( dpvertexbuffer *vb );
        //generate bundle
        dpapi_bundle *makeBundle( dpmatrix *mx, dpapi_vertexbuffer *vb, dpapi_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1 );
        //generate bundle
        dpapi_bundle *makeBundle( dpmatrix *mx, dpapi_bundle *bdle, float opacity );
        //generate index buffer
        dpapi_indexbuffer *makeIndexBuffer( dpindexbuffer *ib );
        //generate texture
        dpapi_texture *makeTexture( dpbitmap_32bit_uncompressed *bm );
        //return screen width
        unsigned int getWidth( void );
        //return screen height
        unsigned int getHeight( void );

    };

}

#endif








