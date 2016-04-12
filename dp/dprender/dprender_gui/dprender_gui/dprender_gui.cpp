
/*
*/

#include "dprender_gui.h"
#include "dprender_gui_ref.h"
#include "dprender_gui_readlock.h"
#include "dprender_gui_writelock.h"
#include "../../../dpgfx/dpgui/dpgui.h"
#include "../../../dpgfx/dpgui/dpgui_readlock.h"

#include "../../dpapi/dpapi/dpapi_vertexbuffer/dpapi_vertexbuffer.h"
#include "../../dpapi/dpapi/dpapi_indexbuffer/dpapi_indexbuffer.h"
#include "../../dpapi/dpapi/dpapi_texture/dpapi_texture.h"
#include "../../dpapi/dpapi/dpapi_bundle/dpapi_bundle.h"

#include "../../../dpgfx/dpvertex/dpvertexbuffer.h"
#include "../../../dpgfx/dpvertex/dpindexbuffer.h"
#include "../../../dpgfx/dpmatrix/dpmatrix.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist_writelock.h"


namespace dp
{

    //ctor
    dprender_gui::dprender_gui( dpgui *pg ) : dprender_gui_list()
    {
        this->setSync( pg );

        this->t_bg = this->t_fg = 0;
        this->vb = 0;
        this->ib_bg = this->ib_fg = 0;
        this->bdle_bg = 0;
        this->bdle_fg = 0;
    }

    //dtor
    dprender_gui::~dprender_gui( void )
    {
        if( this->bdle_fg )
            delete this->bdle_fg;
        if( this->bdle_bg )
            delete this->bdle_bg;
        if( this->ib_bg )
            delete this->ib_bg;
        if( this->ib_fg )
            delete this->ib_fg;
        if( this->vb )
            delete this->vb;
        if( this->t_bg )
            delete this->t_bg;
        if( this->t_fg )
            delete this->t_fg;
    }

    //generate readlock
    dpshared_readlock *dprender_gui::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_gui_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender_gui::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_gui_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender_gui::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_gui_ref( this, k, t_sync );
    }

    //set dimensions
    void dprender_gui::setDimensions( unsigned int w, unsigned int h )
    {
        this->rc.w = w;
        this->rc.h = h;
    }

    //set position
    void dprender_gui::setPosition( int x, int y )
    {
        this->rc.x = x;
        this->rc.y = y;
    }

    //get dimensions
    void dprender_gui::getDimensions( unsigned int *w, unsigned int *h )
    {
        *w = this->rc.w;
        *h = this->rc.h;
    }

    //get position
    void dprender_gui::getPosition( int *x, int *y )
    {
        *x = this->rc.x;
        *y = this->rc.y;
    }

    //return z
    unsigned int dprender_gui::getZ( void )
    {
        return this->z;
    }

    //set z
    void dprender_gui::setZ( unsigned int z )
    {
        this->z = z;
    }

    //override to handle sync copy, be sure to call base class first!
    void dprender_gui::onSync( dpshared_readlock *psync )
    {
        dpgui_readlock *gr;

        this->dprender_gui_list::onSync( psync );

        if( !psync->isSyncType( "dpgui" ) )
            return;
        gr = (dpgui_readlock *)psync;

        gr->getDimensions( &this->rc.w, &this->rc.h );
        gr->getPosition( &this->rc.x, &this->rc.y );
        this->z = gr->getZ();

        this->makeVB( this->ctx );
        this->makeBgIB( this->ctx );
        this->makeFgIB( this->ctx );

        if( this->makeBgTex( this->ctx, gr ) || !this->bdle_bg )
        {
            if( this->bdle_bg )
                delete this->bdle_bg;
            this->bdle_bg = ctx->makeBundle( this->vb, this->ib_bg, 0, this->t_bg, 0 );
        }

        if( this->makeFgTex( this->ctx, gr ) || !this->bdle_fg )
        {
            if( this->bdle_fg )
                delete this->bdle_fg;
            this->bdle_fg = ctx->makeBundle( this->vb, this->ib_fg, 0, this->t_fg, 0 );
        }
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dprender_gui::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( s.compare( "dprender_gui" ) == 0 )
            return 1;

        return this->dprender_gui_list::isSyncType( ctypename );
    }

    //override to handle processing
    void dprender_gui::onRun( dpshared_writelock *wl )
    {
        this->dprender_gui_list::onRun( wl );
    }

    //pass in context
    void dprender_gui::passContext( dpapi_context_writelock *ctx )
    {
        this->ctx = ctx;
        this->dprender_gui_list::passContext( ctx );
    }

    //render
    void dprender_gui::render( dpmatrix *m_parent, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
//        dpmatrix m;
        if( !this->bdle_bg || !this->bdle_fg )
            return;

        cll->addBundle( ctx, this->bdle_bg );
        cll->addBundle( ctx, this->bdle_fg );
    }

    //make matrix
    void dprender_gui::calcMatrix( dpmatrix *mparent )
    {

    }

    //make bg texture, return false if not remade/up-to-date
    bool dprender_gui::makeBgTex( dpapi_context_writelock *ctx, dpgui_readlock *g )
    {
        dpbitmap *bm;

        if( this->t_bg && g->getBgTime() == this->bg_time )
            return 0;

        if( this->t_bg )
            delete this->t_bg;

        bm = g->getBg();
        this->t_bg = ctx->makeTexture( bm );
        return 1;
    }

    //make bg texture, return false if not remade/up-to-date
    bool dprender_gui::makeFgTex( dpapi_context_writelock *ctx, dpgui_readlock *g )
    {
        dpbitmap *bm;

        if( this->t_fg && g->getFgTime() == this->fg_time )
            return 0;

        if( this->t_fg )
            delete this->t_fg;

        bm = g->getFg();
        this->t_fg = ctx->makeTexture( bm );
        return 1;
    }

    //create vertex buffer
    void dprender_gui::makeVB( dpapi_context_writelock *ctx )
    {
        dpvertexbuffer vb;
        dpvertex v;

        if( this->vb )
            return;

        v.vert.z = -1;
        v.norm.x = 0;
        v.norm.y = 0;
        v.norm.z = 1;

        //tl
        v.vert.x = -1;
        v.vert.y = 1;
        v.texcoord[ 0 ].s = 0;
        v.texcoord[ 0 ].t = 1;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        //tr
        v.vert.x = 1;
        v.vert.y = 1;
        v.texcoord[ 0 ].s = 1;
        v.texcoord[ 0 ].t = 1;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        //bl
        v.vert.x = -1;
        v.vert.y = -1;
        v.texcoord[ 0 ].s = 0;
        v.texcoord[ 0 ].t = 0;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        //br
        v.vert.x = 1;
        v.vert.y = -1;
        v.texcoord[ 0 ].s = 1;
        v.texcoord[ 0 ].t = 0;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        this->vb = ctx->makeVertexBuffer( &vb );
    }

    //create bg index buffer
    void dprender_gui::makeBgIB( dpapi_context_writelock *ctx )
    {
        dpindexbuffer ib;
        dpindex i;

        if( this->ib_bg )
            return;

        //tl
        i.i = 0;
        ib.write( &i );

        //bl
        i.i = 2;
        ib.write( &i );

        //tr
        i.i = 1;
        ib.write( &i );

        //tr
        i.i = 1;
        ib.write( &i );

        //bl
        i.i = 2;
        ib.write( &i );

        //br
        i.i = 3;
        ib.write( &i );

        this->ib_bg = ctx->makeIndexBuffer( &ib );
    }

    //create fg index buffer
    void dprender_gui::makeFgIB( dpapi_context_writelock *ctx )
    {
        dpindexbuffer ib;
        dpindex i;

        if( this->ib_fg )
            return;

        //tl
        i.i = 0;
        ib.write( &i );

        //bl
        i.i = 2;
        ib.write( &i );

        //tr
        i.i = 1;
        ib.write( &i );

        //tr
        i.i = 1;
        ib.write( &i );

        //bl
        i.i = 2;
        ib.write( &i );

        //br
        i.i = 3;
        ib.write( &i );

        this->ib_fg = ctx->makeIndexBuffer( &ib );
    }

}






