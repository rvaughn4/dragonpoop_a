
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

#include <string.h>

#if defined dprender_gui_input_debug
#include <iostream>
#endif // defined

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

        memset( &this->attr, 0, sizeof( this->attr ) );
        this->t_spin = this->getTicks();

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

    //return z
    unsigned int dprender_gui::getZ( void )
    {
        return this->attr.g.z;
    }

    //override to handle sync copy, be sure to call base class first!
    void dprender_gui::onSync( dpshared_readlock *psync )
    {
        dpgui_readlock *gr;

        this->dprender_gui_list::onSync( psync );

        if( !psync->isSyncType( "dpgui" ) )
            return;
        gr = (dpgui_readlock *)psync;
        gr->getAttributes( &this->attr.g );

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

        if( this->attr.bHide )
            return;

        cll->addBundle( ctx, &this->sz_mat, this->bdle_bg );
        cll->addBundle( ctx, &this->sz_mat, this->bdle_fg );

        this->dprender_gui_list::render( wl, m_world, rc_world, &this->mat, &this->attr.rc_exact, ctx, cll );
    }

    //process input event
    bool dprender_gui::processEvent( dprender_gui_list_writelock *l, dpinput_event *e )
    {
        dpgui_writelock *gl;
        dpshared_guard g;
        dpinput_event ce;
        dpgui_attribs a;

        if( this->attr.bHide )
            return 0;

        if( !this->attr.g.bIsMin || !this->attr.g.bIsFloat )
        {
            switch( e->h.etype )
            {
                case dpinput_event_type_leftclick:
                    this->attr.bIsFocus = 0;
                    if( this->dprender_gui_list::processEvent( l, e ) )
                    {
                        #if defined dprender_gui_input_debug
                        std::cout << "passed on left click to child " << e->mse.x << " " << e->mse.y << "\r\n";
                        #endif // defined
                        return 1;
                    }
                    break;
                case dpinput_event_type_rightclick:
                    this->attr.bIsFocus = 0;
                    if( this->dprender_gui_list::processEvent( l, e ) )
                    {
                        #if defined dprender_gui_input_debug
                        std::cout << "passed on right click to child " << e->mse.x << " " << e->mse.y << "\r\n";
                        #endif // defined
                        return 1;
                    }
                    break;
                case dpinput_event_type_mouse:
                    if( this->dprender_gui_list::processEvent( l, e ) )
                    {
                        #if defined dprender_gui_input_debug
                        std::cout << "passed on mouse move to child " << e->mse.x << " " << e->mse.y << "\r\n";
                        #endif // defined
                        return 1;
                    }
                    break;
                default:
                    if( !this->attr.bIsFocus && this->dprender_gui_list::processEvent( l, e ) )
                    {
                        #if defined dprender_gui_input_debug
                        std::cout << "passed on other event to child\r\n";
                        #endif // defined
                        return 1;
                    }
            }
        }

        switch( e->h.etype )
        {
            case dpinput_event_type_leftclick:
            case dpinput_event_type_rightclick:
                this->attr.bIsFocus = 0;

            case dpinput_event_type_mouse:

                ce = *e;
                e = &ce;

                e->mse.x = ( e->mse.x / e->mse.w ) * 2.0f - 1.0f;
                e->mse.y = -( ( e->mse.y / e->mse.h ) * 2.0f - 1.0f );
                this->attr.mousepos.x = e->mse.sx;
                this->attr.mousepos.y = e->mse.sy;

                this->undo_mat.transform( &e->mse.x, &e->mse.y, 0, 0 );

                this->attr.bIsMouseOver = 0;
                this->attr.bIsMouseDown = e->mse.isDown;
                if( !this->attr.bIsDrag || !this->attr.g.bIsFloat )
                {
                    if( e->mse.x < 0 || e->mse.y < 0 || e->mse.x > this->attr.g.rc.w || e->mse.y > this->attr.g.rc.h )
                        return 0;
                }
                this->attr.bIsMouseOver = 1;
                #if defined dprender_gui_input_debug
                std::cout << "caught mouse " << e->mse.x << " " << e->mse.y << "\r\n";
                #endif // defined

                switch( e->h.etype )
                {
                    case dpinput_event_type_leftclick:
                    case dpinput_event_type_rightclick:
                        this->attr.bIsFocus = 1;
                        break;
                }

                if( !this->attr.bIsDrag && e->mse.isDown && !e->mse.isRight && this->attr.g.bIsFloat )
                {
                    this->attr.bIsDrag = 1;
                    this->attr.drag_start.x = e->mse.sx;
                    this->attr.drag_start.y = e->mse.sy;
                    this->attr.bIsSize = 0;

                    if( !this->attr.g.bIsMin )
                    {
                        if( e->mse.x > this->attr.rc_exact.w - 50 )
                            this->attr.bIsSize = 1;
                        if( e->mse.y > this->attr.rc_exact.h - 50 )
                            this->attr.bIsSize = 1;
                    }
                }
                if( this->attr.bIsDrag && !e->mse.isDown )
                {
                    this->attr.bIsDrag = 0;
                    if( this->attr.g.bIsMin )
                    {
                        if( abs( this->attr.drag_off.x ) + abs( this->attr.drag_off.y ) < 0.1f )
                        {
                            this->attr.g.bIsMin = 0;
                            gl = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->pgui, 100 );
                            if( gl )
                            {
                                gl->getAttributes( &a );
                                a.bIsMin = 0;
                                gl->setAttributes( &a );
                                gl->update();
                            }
                            g.release( gl );
                        }
                        else
                        {
                            this->attr.min_pos.x += this->attr.drag_off.x;
                            this->attr.min_pos.y += this->attr.drag_off.y;
                            if( this->attr.min_pos.x < 0 )
                                this->attr.min_pos.x = 0;
                            if( this->attr.min_pos.x > e->mse.sw - 50 )
                                this->attr.min_pos.x = e->mse.sw - 50;
                            if( this->attr.min_pos.y < 0 )
                                this->attr.min_pos.y = 0;
                            if( this->attr.min_pos.y > e->mse.sh - 50 )
                                this->attr.min_pos.y = e->mse.sh - 50;
                        }
                    }
                    else
                    {
                        if( this->attr.bIsSize )
                        {
                            this->attr.g.rc.w += this->attr.drag_off.x;
                            this->attr.g.rc.h += this->attr.drag_off.y;
                            if( this->attr.g.rc.w < 50 )
                                this->attr.g.rc.w = 50;
                            if( this->attr.g.rc.h < 50 )
                                this->attr.g.rc.h = 50;
                        }
                        else
                        {
                            this->attr.g.rc.x += this->attr.drag_off.x;
                            this->attr.g.rc.y += this->attr.drag_off.y;
                            if( this->attr.g.rc.x < 0 )
                                this->attr.g.rc.x = 0;
                            if( this->attr.g.rc.x > e->mse.sw - this->attr.g.rc.w )
                                this->attr.g.rc.x = e->mse.sw - this->attr.g.rc.w;
                            if( this->attr.g.rc.y < 0 )
                                this->attr.g.rc.y = 0;
                            if( this->attr.g.rc.y > e->mse.sh - this->attr.g.rc.h )
                                this->attr.g.rc.y = e->mse.sh - this->attr.g.rc.h;
                        }

                        gl = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->pgui, 100 );
                        if( gl )
                        {
                            gl->getAttributes( &a );
                            a.rc = this->attr.g.rc;
                            gl->setAttributes( &a );
                            gl->update();
                        }
                        g.release( gl );
                    }
                }
                if( this->attr.bIsDrag )
                {
                    this->attr.drag_off.x = e->mse.sx - this->attr.drag_start.x;
                    this->attr.drag_off.y = e->mse.sy - this->attr.drag_start.y;
                }

                break;
            case dpinput_event_type_keypress:
            case dpinput_event_type_text:
                if( this->attr.g.bIsMin || ( !this->attr.g.bIsInput && !this->attr.g.bIsSelect ) )
                    return 0;
                #if defined dprender_gui_input_debug
                std::cout << "caught other event\r\n";
                #endif // defined
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

        if( this->attr.g.bFillHor )
        {
            this->attr.g.rc.x = 0;
            this->attr.g.rc.w = rc_parent->w;
            this->attr.g.align = dpgui_alignment_left;
        }

        switch( this->attr.g.align )
        {
            case dpgui_alignment_right:
                pos.x = rc_parent->w - this->attr.g.rc.x - this->attr.g.rc.w;
                pos.y = this->attr.g.rc.y;
                break;

            case dpgui_alignment_center:
                pos.x = ( rc_parent->w - this->attr.g.rc.w ) / 2 + this->attr.g.rc.x;
                pos.y = ( rc_parent->h - this->attr.g.rc.h ) / 2 + this->attr.g.rc.y;
                break;

            case dpgui_alignment_left:

            default:
                pos.x = this->attr.g.rc.x;
                pos.y = this->attr.g.rc.y;
                break;
        }

        pos.x += rc_parent->x;
        pos.y += rc_parent->y;
        pos.z = 16.0f + (float)this->attr.g.z / -8.0f;
        if( pos.z < 0.01f )
            pos.z = 0.01f;

        this->attr.zoom += ( this->attr.g.zoom - this->attr.zoom ) * 0.5f * anim_s;
        sz.x = this->attr.g.rc.w * this->attr.zoom;
        sz.y = this->attr.g.rc.h * this->attr.zoom;
        sz.z = 0;

        if( this->attr.bIsMouseOver && !this->attr.bIsMouseDown && this->attr.g.bGrows )
        {
            ft = 30.0f * 10.0f;
            if( sz.x < ft )
                ft = sz.x;
            if( sz.y < ft )
                ft = sz.y;
            ft = ft / 10.0f;
            this->attr.fhover += ( ft - this->attr.fhover ) * 0.4f * anim_s;
        }
        else
            this->attr.fhover += ( 0.0f - this->attr.fhover ) * 0.4f * anim_s;

        if( this->attr.g.bIsMin )
            this->attr.fMin += ( 1.0f - this->attr.fMin ) * 0.4f * anim_s;
        else
            this->attr.fMin += ( 0.0f - this->attr.fMin ) * 0.4f * anim_s;

        if( this->attr.g.bIsFloat || this->attr.g.bIsFollow )
        {
            m_parent = m_world;
            rc_parent = rc_world;
        }

        if( this->attr.g.bIsFollow )
        {
            pos.x = this->attr.mousepos.x;
            pos.y = this->attr.mousepos.y;
        }
        if( this->attr.g.bIsCenter && !this->attr.g.bIsFollow )
        {
            pos.x = ( rc_parent->w - sz.x ) * 0.5f;
            pos.y = ( rc_parent->h - sz.y ) * 0.5f;
        }

        this->attr.bHide = 0;
        if( pos.x > rc_parent->w || pos.y > rc_parent->h )
            this->attr.bHide = 1;

        pos.x = pos.x * ( 1.0f - this->attr.fMin ) + this->attr.min_pos.x * this->attr.fMin;
        pos.y = pos.y * ( 1.0f - this->attr.fMin ) + this->attr.min_pos.y * this->attr.fMin;
        msc.x = ( sz.x * ( 1.0f - this->attr.fMin ) + 50.0f * this->attr.fMin ) / sz.x;
        msc.y = ( sz.y * ( 1.0f - this->attr.fMin ) + 50.0f * this->attr.fMin ) / sz.y;
        msc.z = 1.0f;

        if( this->attr.bIsDrag )
        {
            if( this->attr.bIsSize )
            {
                sz.x += this->attr.drag_off.x;
                sz.y += this->attr.drag_off.y;
            }
            else
            {
                pos.x += this->attr.drag_off.x;
                pos.y += this->attr.drag_off.y;
            }
        }

        pos.x -= this->attr.fhover;
        pos.y -= this->attr.fhover;
        sz.x += this->attr.fhover + this->attr.fhover;
        sz.y += this->attr.fhover + this->attr.fhover;

        this->attr.rc_exact.x = this->attr.g.scroll.x;
        this->attr.rc_exact.y = this->attr.g.scroll.y;
        this->attr.rc_exact.w = sz.x;
        this->attr.rc_exact.h = sz.y;

        if( m_parent )
            this->mat.copy( m_parent );
        else
            this->mat.setIdentity();

        t -= this->t_spin;
        ft = (float)t / 1000.0f;

        rot = this->attr.g.rot;
        rot.x += this->attr.g.spin.x * ft;
        rot.y += this->attr.g.spin.y * ft;
        rot.z += this->attr.g.spin.z * ft;

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
        dpgui_attribs a;

        g->getAttributes( &a );
        if( this->t_bg && a.bg_time == this->attr.bg_time )
            return 0;

        bm = g->getBg();
        if( !bm )
            return 0;

        if( this->t_bg_old )
            delete this->t_bg_old;
        this->t_bg_old = this->t_bg;

        this->t_bg = ctx->makeTexture( bm );
        this->attr.bg_time = a.bg_time;
        return 1;
    }

    //make bg texture, return false if not remade/up-to-date
    bool dprender_gui::makeFgTex( dpapi_context_writelock *ctx, dpgui_readlock *g )
    {
        dpbitmap_32bit_uncompressed *bm;
        dpgui_attribs a;

        g->getAttributes( &a );
        if( this->t_fg && a.fg_time == this->attr.fg_time )
            return 0;

        bm = g->getFg();
        if( !bm )
            return 0;

        if( this->t_fg_old )
            delete this->t_fg_old;
        this->t_fg_old = this->t_fg;

        this->t_fg = ctx->makeTexture( bm );
        this->attr.fg_time = a.fg_time;
        return 1;
    }

    //create vertex buffer
    bool dprender_gui::makeVB( dpapi_context_writelock *ctx, dpgui_readlock *g )
    {
        dpvertexbuffer vb;
        dpvertex v;

        if( this->vb )
            return 0;

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
        v.vert.x = 1;
        v.vert.y = 0;
        v.texcoord[ 0 ].s = 1;
        v.texcoord[ 0 ].t = 1;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        //bl
        v.vert.x = 0;
        v.vert.y = 1;
        v.texcoord[ 0 ].s = 0;
        v.texcoord[ 0 ].t = 0;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        //br
        v.vert.x = 1;
        v.vert.y = 1;
        v.texcoord[ 0 ].s = 1;
        v.texcoord[ 0 ].t = 0;
        v.texcoord[ 1 ] = v.texcoord[ 0 ];
        vb.write( &v );

        this->vb = ctx->makeVertexBuffer( &vb );

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






