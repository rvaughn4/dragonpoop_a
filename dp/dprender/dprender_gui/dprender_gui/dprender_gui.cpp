
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

        this->t_bg = this->t_fg = this->t_fg_old = this->t_bg_old = 0;
        this->vb = 0;
        this->ib_bg = this->ib_fg = 0;
        this->bdle_bg = 0;
        this->bdle_fg = 0;
        this->z = pg->getZ();
        this->bIsMouseOver = 0;
        this->t_spin = this->getTicks();
        this->bMin = 0;
        this->fMin = 0;

        this->min_pos.x = 0;
        this->min_pos.y = 0;
        this->bIsDrag = 0;
        this->bFocus = 0;
        this->bHide = 0;

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
        if( this->t_bg_old )
            delete this->t_bg_old;
        if( this->t_fg_old )
            delete this->t_fg_old;

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

        this->bIsCentered = gr->isCentered();
        this->bIsFloating = gr->isFloating();
        this->bFollowCursor = gr->isFollowingCursor();
        this->bGrows = gr->doesGrow();
        this->bMin = gr->isMinimized();
        this->align = gr->getAlignment();
        this->zoom = gr->getZoom();
        this->bHorizFill = gr->isHorizFill();
        this->bIsInput = gr->isInput();
        this->bIsSelect = gr->isSelect();

        gr->getRotation( &this->rot );
        gr->getSpin( &this->rot );
        this->scroll.x = 0;
        this->scroll.y = 0;

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

        if( this->bHide )
            return;

        cll->addBundle( ctx, &this->sz_mat, this->bdle_bg );
        cll->addBundle( ctx, &this->sz_mat, this->bdle_fg );

        this->dprender_gui_list::render( wl, m_world, rc_world, &this->mat, &this->rc_exact, ctx, cll );
    }

    //process input event
    bool dprender_gui::processEvent( dprender_gui_list_writelock *l, dpinput_event *e )
    {
        dpgui_writelock *gl;
        dpshared_guard g;
        dpinput_event ce;

        if( this->bHide )
            return 0;

        if( !this->bMin || !this->bIsFloating )
        {
            switch( e->h.etype )
            {
                case dpinput_event_type_leftclick:
                case dpinput_event_type_rightclick:
                    this->bFocus = 0;
                case dpinput_event_type_mouse:
                    if( this->dprender_gui_list::processEvent( l, e ) )
                        return 1;
                    break;
                default:
                    if( !this->bFocus && this->dprender_gui_list::processEvent( l, e ) )
                        return 1;

            }
        }

        switch( e->h.etype )
        {
            case dpinput_event_type_leftclick:
            case dpinput_event_type_rightclick:
                this->bFocus = 0;

            case dpinput_event_type_mouse:

                ce = *e;
                e = &ce;

                e->mse.x = ( e->mse.x / e->mse.w ) * 2.0f - 1.0f;
                e->mse.y = -( ( e->mse.y / e->mse.h ) * 2.0f - 1.0f );
                this->mousepos.x = e->mse.sx;
                this->mousepos.y = e->mse.sy;

                this->undo_mat.transform( &e->mse.x, &e->mse.y, 0, 0 );

                this->bIsMouseOver = 0;
                this->bIsMouseDown = e->mse.isDown;
                if( !this->bIsDrag || !this->bIsFloating )
                {
                    if( e->mse.x < 0 || e->mse.y < 0 || e->mse.x > this->rc.w || e->mse.y > this->rc.h )
                        return 0;
                }
                this->bIsMouseOver = 1;

                switch( e->h.etype )
                {
                    case dpinput_event_type_leftclick:
                    case dpinput_event_type_rightclick:
                        this->bFocus = 1;
                        break;
                }

                if( !this->bIsDrag && e->mse.isDown && !e->mse.isRight && this->bIsFloating )
                {
                    this->bIsDrag = 1;
                    this->drag_start.x = e->mse.sx;
                    this->drag_start.y = e->mse.sy;
                    this->bIsSize = 0;

                    if( !this->bMin )
                    {
                        if( e->mse.x > this->rc_exact.w - 50 )
                            this->bIsSize = 1;
                        if( e->mse.y > this->rc_exact.h - 50 )
                            this->bIsSize = 1;
                    }
                }
                if( this->bIsDrag && !e->mse.isDown )
                {
                    this->bIsDrag = 0;
                    if( this->bMin )
                    {
                        if( abs( this->drag_off.x ) + abs( this->drag_off.y ) < 0.1f )
                        {
                            this->bMin = 0;
                            gl = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->pgui, 100 );
                            if( gl )
                            {
                                gl->setMinimized( 0 );
                                gl->update();
                            }
                            g.release( gl );
                        }
                        else
                        {
                            this->min_pos.x += this->drag_off.x;
                            this->min_pos.y += this->drag_off.y;
                            if( this->min_pos.x < 0 )
                                this->min_pos.x = 0;
                            if( this->min_pos.x > e->mse.sw - 50 )
                                this->min_pos.x = e->mse.sw - 50;
                            if( this->min_pos.y < 0 )
                                this->min_pos.y = 0;
                            if( this->min_pos.y > e->mse.sh - 50 )
                                this->min_pos.y = e->mse.sh - 50;
                        }
                    }
                    else
                    {
                        if( this->bIsSize )
                        {
                            this->rc.w += this->drag_off.x;
                            this->rc.h += this->drag_off.y;
                            if( this->rc.w < 50 )
                                this->rc.w = 50;
                            if( this->rc.h < 50 )
                                this->rc.h = 50;
                        }
                        else
                        {
                            this->rc.x += this->drag_off.x;
                            this->rc.y += this->drag_off.y;
                            if( this->rc.x < 0 )
                                this->rc.x = 0;
                            if( this->rc.x > e->mse.sw - this->rc.w )
                                this->rc.x = e->mse.sw - this->rc.w;
                            if( this->rc.y < 0 )
                                this->rc.y = 0;
                            if( this->rc.y > e->mse.sh - this->rc.h )
                                this->rc.y = e->mse.sh - this->rc.h;
                        }

                        gl = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->pgui, 100 );
                        if( gl )
                        {
                            if( this->bIsSize )
                                gl->setDimensions( this->rc.w, this->rc.h );
                            else
                                gl->setPosition( this->rc.x, this->rc.y );
                            gl->update();
                        }
                        g.release( gl );
                    }
                }
                if( this->bIsDrag )
                {
                    this->drag_off.x = e->mse.sx - this->drag_start.x;
                    this->drag_off.y = e->mse.sy - this->drag_start.y;
                }

                break;
            case dpinput_event_type_keypress:
            case dpinput_event_type_text:
                if( this->bMin || ( !this->bIsInput && !this->bIsSelect ) )
                    return 0;
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
        dpxyzw pos, sz, rot, msc;
        dpmatrix m;
        uint64_t t, d;
        float ft, anim_s;

        t = this->getTicks();
        d = t - this->t_last_ftime;
        this->t_last_ftime = t;
        anim_s = (float)d / 30.0f;

        if( this->bHorizFill )
        {
            this->rc.x = 0;
            this->rc.w = rc_parent->w;
            this->align = dpgui_alignment_left;
        }

        switch( this->align )
        {
            case dpgui_alignment_right:
                pos.x = rc_parent->w - this->rc.x - this->rc.w;
                pos.y = this->rc.y;
                break;

            case dpgui_alignment_center:
                pos.x = ( rc_parent->w - this->rc.w ) / 2 + this->rc.x;
                pos.y = ( rc_parent->h - this->rc.h ) / 2 + this->rc.y;
                break;

            case dpgui_alignment_left:

            default:
                pos.x = this->rc.x;
                pos.y = this->rc.y;
                break;
        }

        pos.x += rc_parent->x;
        pos.y += rc_parent->y;
        pos.z = 16.0f + (float)this->z / -8.0f;
        if( pos.z < 0.01f )
            pos.z = 0.01f;
        sz.x = this->rc.w * this->zoom;
        sz.y = this->rc.h * this->zoom;
        sz.z = 0;

        if( this->bIsMouseOver && !this->bIsMouseDown && this->bGrows )
        {
            ft = 30.0f * 10.0f;
            if( sz.x < ft )
                ft = sz.x;
            if( sz.y < ft )
                ft = sz.y;
            ft = ft / 10.0f;
            this->fhover += ( ft - this->fhover ) * 0.4f * anim_s;
        }
        else
            this->fhover += ( 0.0f - this->fhover ) * 0.4f * anim_s;

        if( this->bMin )
            this->fMin += ( 1.0f - this->fMin ) * 0.4f * anim_s;
        else
            this->fMin += ( 0.0f - this->fMin ) * 0.4f * anim_s;

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
        if( this->bIsCentered && !this->bFollowCursor )
        {
            pos.x = ( rc_parent->w - sz.x ) * 0.5f;
            pos.y = ( rc_parent->h - sz.y ) * 0.5f;
        }

        this->bHide = 0;
        if( pos.x > rc_parent->w || pos.y > rc_parent->h )
            this->bHide = 1;

        pos.x = pos.x * ( 1.0f - this->fMin ) + this->min_pos.x * this->fMin;
        pos.y = pos.y * ( 1.0f - this->fMin ) + this->min_pos.y * this->fMin;
        msc.x = ( sz.x * ( 1.0f - this->fMin ) + 50.0f * this->fMin ) / sz.x;
        msc.y = ( sz.y * ( 1.0f - this->fMin ) + 50.0f * this->fMin ) / sz.y;
        msc.z = 1.0f;

        if( this->bIsDrag )
        {
            if( this->bIsSize )
            {
                sz.x += this->drag_off.x;
                sz.y += this->drag_off.y;
            }
            else
            {
                pos.x += this->drag_off.x;
                pos.y += this->drag_off.y;
            }
        }

        pos.x -= this->fhover;
        pos.y -= this->fhover;
        sz.x += this->fhover + this->fhover;
        sz.y += this->fhover + this->fhover;

        this->rc_exact.x = this->scroll.x;
        this->rc_exact.y = this->scroll.y;
        this->rc_exact.w = sz.x;
        this->rc_exact.h = sz.y;

        if( m_parent )
            this->mat.copy( m_parent );
        else
            this->mat.setIdentity();

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
        this->mat.translate( sz.x * -0.5f, sz.y * -0.5f, sz.z * -0.5f );

        this->mat.scale( msc.x, msc.y, msc.z );

        this->undo_mat.inverse( &this->mat );
        this->sz_mat.copy( &this->mat );
        this->sz_mat.scale( sz.x, sz.y, 1.0f );
    }

    //make bg texture, return false if not remade/up-to-date
    bool dprender_gui::makeBgTex( dpapi_context_writelock *ctx, dpgui_readlock *g )
    {
        dpbitmap_32bit_uncompressed *bm;

        if( this->t_bg && g->getBgTime() == this->bg_time )
            return 0;

        bm = g->getBg();
        if( !bm )
            return 0;

        if( this->t_bg_old )
            delete this->t_bg_old;
        this->t_bg_old = this->t_bg;

        this->t_bg = ctx->makeTexture( bm );
        this->bg_time = g->getBgTime();
        return 1;
    }

    //make bg texture, return false if not remade/up-to-date
    bool dprender_gui::makeFgTex( dpapi_context_writelock *ctx, dpgui_readlock *g )
    {
        dpbitmap_32bit_uncompressed *bm;

        if( this->t_fg && g->getFgTime() == this->fg_time )
            return 0;

        bm = g->getFg();
        if( !bm )
            return 0;

        if( this->t_fg_old )
            delete this->t_fg_old;
        this->t_fg_old = this->t_fg;

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

        if( this->vb )//&& g->getSzTime() == this->sz_time )
            return 0;

        if( this->vb )
            delete this->vb;

        w = 1.0f;//(float)this->rc.w;
        h = 1.0f;//(float)this->rc.h;

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

    //compare gui
    bool dprender_gui::compare( dpgui *g )
    {
        if( !this->pgui )
            return 0;
        return this->pgui->isParent( g );
    }

    //returns true if linked
    bool dprender_gui::isGuiLinked( void )
    {
        dpgui_readlock *l;
        dpshared_guard g;

        if( !this->pgui )
            return 0;
        if( !this->pgui->isLinked() )
            return 0;

        l = (dpgui_readlock *)dpshared_guard_tryReadLock_timeout( g, this->pgui, 10 );
        if( !l )
            return 1;

        return l->isRun();
    }

}






