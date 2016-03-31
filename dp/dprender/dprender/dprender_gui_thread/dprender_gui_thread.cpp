
/*

*/

#include "dprender_gui_thread.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"
#include "../../dpapi/dpapi/dpapi/dpapi_factory.h"
#include "../../dpapi/dpapi/dpapi/dpapi.h"
#include "../../dpapi/dpapi/dpapi/dpapi_writelock.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist_writelock.h"
#include "../dprender/dprender.h"
#include "../../../dpdefines.h"

#include "../../dpapi/dpapi/dpapi_indexbuffer/dpapi_indexbuffer.h"
#include "../../dpapi/dpapi/dpapi_vertexbuffer/dpapi_vertexbuffer.h"
#include "../../dpapi/dpapi/dpapi_bundle/dpapi_bundle.h"
#include "../../dpapi/dpapi/dpapi_texture/dpapi_texture.h"

#include "../../../dpgfx/dpvertex/dpindexbuffer.h"
#include "../../../dpgfx/dpvertex/dpvertexbuffer.h"
#include "../../../dpgfx/dpbitmap/dpbitmap/dpbitmap.h"
#include "../../../dpgfx/dpbitmap/dpbitmap_loader/dpbitmap_loader.h"

#if defined dprender_debug
#include <iostream>
#endif // defined

namespace dp
{

    //ctor
    dprender_gui_thread::dprender_gui_thread( dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b ) : dprender_scene_thread( ctx, cl_a, cl_b, flag_a, flag_b )
    {
        this->ib = 0;
        this->vb = 0;
        this->bdle = 0;
        this->t = 0;
    }

    //dtor
    dprender_gui_thread::~dprender_gui_thread( void )
    {
        this->waitForStop();
        this->unlink();
    }

    //override to handle scene start
    bool dprender_gui_thread::onSceneStart( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx )
    {
        dpvertexbuffer vb;
        dpindexbuffer ib;
        dpbitmap_loader bl;
        dpbitmap *bm;
        dpindex i;

        bm = bl.load( "palmtrees.png" );
        this->t = ctx->makeTexture( bm );
        delete bm;

        i.i = 0;
        ib.write( &i );
        i.i = 1;
        ib.write( &i );
        i.i = 2;
        ib.write( &i );

        dpvertex v;

        v.vert.x = 0;
        v.vert.y = 0;
        v.vert.z = 0;
        v.texcoord[0].s = 0;
        v.texcoord[0].t = 0;
        vb.write( &v );
        v.vert.x = 0;
        v.vert.y = -1;
        v.vert.z = 0;
        v.texcoord[0].s = 0;
        v.texcoord[0].t = 1;
        vb.write( &v );
        v.vert.x = 1;
        v.vert.y = -1;
        v.vert.z = 1;
        v.texcoord[0].s = 1;
        v.texcoord[0].t = 1;
        vb.write( &v );

        this->ib = ctx->makeIndexBuffer( &ib );
        this->vb = ctx->makeVertexBuffer( &vb );
        this->bdle = ctx->makeBundle( this->vb, this->ib, 0, this->t, 0 );

        return 1;
    }

    //override to handle scene stop/cleanup
    bool dprender_gui_thread::onSceneStop( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx )
    {
        delete this->bdle;
        delete this->vb;
        delete this->ib;
        delete this->t;
        return 1;
    }

    //override to handle scene render
    bool dprender_gui_thread::onSceneRender( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        cll->addBundle( ctx, this->bdle );
        return 1;
    }

}








