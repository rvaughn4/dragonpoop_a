
/*
*/

#include "dprender_gui.h"
#include "dprender_gui_ref.h"
#include "dprender_gui_readlock.h"
#include "dprender_gui_writelock.h"

#include "../../../dpgfx/dpgui/dpgui.h"
#include "../../../dpgfx/dpgui/dpgui_ref.h"
#include "../../../dpgfx/dpgui/dpgui_readlock.h"
#include "../../../dpgfx/dpgui/dpgui_writelock.h"

#include "../../dpapi/dpapi/dpapi_vertexbuffer/dpapi_vertexbuffer.h"
#include "../../dpapi/dpapi/dpapi_indexbuffer/dpapi_indexbuffer.h"
#include "../../dpapi/dpapi/dpapi_texture/dpapi_texture.h"
#include "../../dpapi/dpapi/dpapi_bundle/dpapi_bundle.h"

#include "../../../dpgfx/dpvertex/dpvertex.h"
#include "../../../dpgfx/dpvertex/dpvertexbuffer.h"
#include "../../../dpgfx/dpvertex/dpindexbuffer.h"
#include "../../../dpgfx/dpmatrix/dpmatrix.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist_writelock.h"

#include "../../dpinput/dpinput.h"
#include "../../dpinput/dpinput_writelock.h"

namespace dp
{

    //ctor
    dprender_gui::dprender_gui( dpgui *pg ) : dprender_gui_list()
    {
        this->setSync( pg );
        this->pgui = (dpgui_ref *)this->g.getRef( pg );

        this->t_bg = this->t_fg = 0;
        this->vb = 0;
        this->ib_bg = this->ib_fg = 0;
        this->bdle_bg = 0;
        this->bdle_fg = 0;
        this->z = pg->getZ();
        this->bIsMouseOver = 0;

        this->inp = 0;
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
        if( this->inp )
            delete this->inp;
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

        this->bIsCentered = 0;
        this->bIsFloating = 0;
        this->bFollowCursor = 0;

        this->rot.x = this->rot.y = this->rot.z = 0;
        this->spin.x = this->spin.y = 0;
        this->spin.z = 45;
        this->t_spin = this->getTicks();

        this->makeVB( this->ctx, gr );
        this->makeBgIB( this->ctx );
        this->makeFgIB( this->ctx );

        if( this->makeBgTex( this->ctx, gr ) || !this->bdle_bg )
        {
            if( this->bdle_bg )
                delete this->bdle_bg;
            this->bdle_bg = ctx->makeBundle( &this->mat, this->vb, this->ib_bg, 0, this->t_bg, 0 );
        }

        if( this->makeFgTex( this->ctx, gr ) || !this->bdle_fg )
        {
            if( this->bdle_fg )
                delete this->bdle_fg;
            this->bdle_fg = ctx->makeBundle( &this->mat, this->vb, this->ib_fg, 0, this->t_fg, 0 );
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
        dpshared_guard g;
        dpgui_writelock *l;

        this->dprender_gui_list::onRun( wl );

        if( !this->inp )
        {
            this->inp = new dpinput();

            l = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->pgui, 2000 );
            if( l )
                l->attachInput( this->inp );
        }
    }

    //pass in context
    void dprender_gui::passContext( dprender_gui_writelock *wl, dpapi_context_writelock *ctx )
    {
        this->ctx = ctx;
        this->dprender_gui_list::passContext( wl, ctx );
    }

    //render
    void dprender_gui::render( dprender_gui_writelock *wl, dpmatrix *m_world, dpbitmap_rectangle *rc_world, dpmatrix *m_parent, dpbitmap_rectangle *rc_parent, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        if( !this->bdle_bg || !this->bdle_fg )
            return;
        this->calcMatrix( m_world, rc_world, m_parent, rc_parent );

        cll->addBundle( ctx, &this->mat_bg, this->bdle_bg );
        cll->addBundle( ctx, &this->mat, this->bdle_fg );

        this->dprender_gui_list::render( wl, m_world, rc_world, &this->mat, &this->rc, ctx, cll );
    }

    //process input event
    bool dprender_gui::processEvent( dprender_gui_list_writelock *l, dpinput_event *e )
    {
        if( this->dprender_gui_list::processEvent( l, e ) )
            return 1;

        switch( e->h.etype )
        {
            case dpinput_event_type_mouse:
            case dpinput_event_type_leftclick:
            case dpinput_event_type_rightclick:

                e->mse.x = ( e->mse.x / e->mse.w ) * 2.0f - 1.0f;
                e->mse.y = -( ( e->mse.y / e->mse.h ) * 2.0f - 1.0f );
                this->mousepos.x = e->mse.sx;
                this->mousepos.y = e->mse.sy;

                this->undo_mat.transform( &e->mse.x, &e->mse.y, 0, 0 );

                this->bIsMouseOver = 0;
                this->bIsMouseDown = e->mse.isDown;
                if( e->mse.x < 0 || e->mse.y < 0 )
                    return 0;
                if( e->mse.x > this->rc.w || e->mse.y > this->rc.h )
                    return 0;
                this->bIsMouseOver = 1;

                break;
        }

        this->onEvent( (dprender_gui_writelock *)l, e );
        return 1;
    }

    //handle event
    void dprender_gui::onEvent( dprender_gui_writelock *l, dpinput_event *e )
    {
        dpinput_writelock *il;
        dpshared_guard g;

        if( !this->inp )
            return;

        il = (dpinput_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->inp, 1000 );
        if( !il )
            return;

        il->addEvent( e );
        il->update();
    }

    //make matrix
    void dprender_gui::calcMatrix( dpmatrix *m_world, dpbitmap_rectangle *rc_world, dpmatrix *m_parent, dpbitmap_rectangle *rc_parent )
    {
        dpxyzw pos, sz, rot, sc;
        dpmatrix m;
        uint64_t t;
        float ft;

static float rr;
rr++;
        pos.x = this->rc.x;
        pos.y = this->rc.y;
        pos.z = 16.0f + (float)this->z / -8.0f;
        if( pos.z < 0.01f )
            pos.z = 0.01f;
        sz.x = this->rc.w;
        sz.y = this->rc.h;
        sz.z = 0;

        if( this->bIsMouseOver && !this->bIsMouseDown )
            this->fhover += (30.0f - this->fhover) * 0.3f;
        else
            this->fhover += (0.0f - this->fhover) * 0.3f;

//        bool bIsCentered, bIsFloating, bFollowCursor;
        if( this->bIsFloating || this->bFollowCursor )
        {
            m_parent = m_world;
            rc_parent = rc_world;
        }
        if( this->bFollowCursor )
        {
            pos.x = this->mousepos.x;
            pos.y = this->mousepos.y;
        }

        pos.x -= this->fhover;
        pos.y -= this->fhover;
        sz.x += this->fhover + this->fhover;
        sz.y += this->fhover + this->fhover;

        sc.x = sz.x / this->rc.w;
        sc.y = sz.y / this->rc.h;
        sc.z = 1.0f;

        if( m_parent )
            this->mat.copy( m_parent );
        else
            this->mat.setIdentity();

        if( this->bIsCentered && !this->bFollowCursor )
        {
            pos.x = ( rc_parent->w - sz.x ) * 0.5f;
            pos.y = ( rc_parent->h - sz.y ) * 0.5f;
        }

        t = this->getTicks();
        t -= this->t_spin;
        ft = (float)t / 1000.0f;

        rot = this->rot;
        rot.x += this->spin.x * ft;
        rot.y += this->spin.y * ft;
        rot.z += this->spin.z * ft;

        this->mat.translate( pos.x, pos.y, pos.z );

        this->mat.translate( sz.x * 0.5f, sz.y * 0.5f, sz.z * 0.5f );
        this->mat.rotateX( rot.x );
        this->mat.rotateY( rot.y );
        this->mat.rotateZ( rot.z );

        this->mat_bg.copy( &this->mat );
        if( this->bIsMouseDown && this->bIsMouseOver )
            this->mat_bg.scale( -1.0f, -1.0f, 1.0f );

        this->mat.translate( sz.x * -0.5f, sz.y * -0.5f, sz.z * -0.5f );
        this->mat.scale( sc.x, sc.y, sc.z );
        this->mat_bg.translate( sz.x * -0.5f, sz.y * -0.5f, sz.z * -0.5f );
        this->mat_bg.scale( sc.x, sc.y, sc.z );

        this->undo_mat.inverse( &this->mat );
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
        this->bg_time = g->getBgTime();
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
        this->fg_time = g->getFgTime();
        return 1;
    }

    //create vertex buffer
    bool dprender_gui::makeVB( dpapi_context_writelock *ctx, dpgui_readlock *g )
    {
        dpvertexbuffer vb;
        dpvertex v;
        float w, h;

        if( this->vb && g->getSzTime() == this->sz_time )
            return 0;

        if( this->vb )
            delete this->vb;

        w = (float)this->rc.w;
        h = (float)this->rc.h;

        v.vert.z = 0;
        v.norm.x = 0;
        v.norm.y = 0;
        v.norm.z = -1;

        //tl
        v.vert.x = 0;
        v.vert.y = 0;
        v.texcoord[ 0 ].s = 0;
        v.texcoord[ 0 ].t = 1;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        //tr
        v.vert.x = w;
        v.vert.y = 0;
        v.texcoord[ 0 ].s = 1;
        v.texcoord[ 0 ].t = 1;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        //bl
        v.vert.x = 0;
        v.vert.y = h;
        v.texcoord[ 0 ].s = 0;
        v.texcoord[ 0 ].t = 0;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        //br
        v.vert.x = w;
        v.vert.y = h;
        v.texcoord[ 0 ].s = 1;
        v.texcoord[ 0 ].t = 0;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        this->vb = ctx->makeVertexBuffer( &vb );
        this->sz_time = g->getSzTime();

        return 1;
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

//reverse side

        //tl
        i.i = 0;
        ib.write( &i );

        //bl //tr
        i.i = 1;
        ib.write( &i );

        //tr //bl
        i.i = 2;
        ib.write( &i );

        //tr
        i.i = 1;
        ib.write( &i );

        //bl //br
        i.i = 3;
        ib.write( &i );

        //br //bl
        i.i = 2;
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






