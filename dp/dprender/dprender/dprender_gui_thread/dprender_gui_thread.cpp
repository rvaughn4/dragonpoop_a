
/*

*/

#include "dprender_gui_thread.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"
#include "../../dpwindow/dpwindow/dpwindow_ref.h"
#include "../../dpapi/dpapi/dpapi/dpapi_factory.h"
#include "../../dpapi/dpapi/dpapi/dpapi.h"
#include "../../dpapi/dpapi/dpapi/dpapi_ref.h"
#include "../../dpapi/dpapi/dpapi/dpapi_readlock.h"
#include "../../dpapi/dpapi/dpapi/dpapi_writelock.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist_writelock.h"
#include "../dprender/dprender.h"
#include "../../../dpgfx/dpscene/dpscene_readlock.h"
#include "../../../dpgfx/dpscene/dpscene_ref.h"
#include "../../dprender_gui/dprender_gui/dprender_gui.h"
#include "../../dprender_gui/dprender_gui/dprender_gui_writelock.h"
#include "../../../dpdefines.h"
#include "../../dpinput/dpinput.h"
#include "../../dpinput/dpinput_writelock.h"
#include "../../../dpgfx/dpbitmap/dpbitmap/dpbitmap.h"
#include "../../../dpgfx/dpgui/dpgui.h"
#include "../../../dpgfx/dpgui/dpgui_readlock.h"

#include <math.h>

namespace dp
{

    //ctor
    dprender_gui_thread::dprender_gui_thread( dpapi_ref *api, dpscene_ref *scn, dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b ) : dprender_scene_thread( api, ctx, cl_a, cl_b, flag_a, flag_b )
    {
        this->inp = 0;
        this->root_gui = 0;
        this->scn = (dpscene_ref *)this->g.getRef( scn );
        this->apir = (dpapi_ref *)this->g.getRef( api );
    }

    //dtor
    dprender_gui_thread::~dprender_gui_thread( void )
    {
        this->waitForStop();
        this->deleteGui();
        this->unlink();

        delete this->inp;
    }

    //override to handle scene start
    bool dprender_gui_thread::onSceneStart( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx )
    {
        this->w = ctx->getWidth();
        this->h = ctx->getHeight();
        this->syncGui();
        return 1;
    }

    //override to handle scene stop/cleanup
    bool dprender_gui_thread::onSceneStop( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx )
    {
        this->deleteGui();
        return 1;
    }

    //override to handle scene render
    bool dprender_gui_thread::onSceneRender( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        this->w = ctx->getWidth();
        this->h = ctx->getHeight();
        this->syncGui();
        this->runInput();
        this->runGui( ctx );
        this->renderGui( ctx, cll );
        return 1;
    }

    //delete gui
    void dprender_gui_thread::deleteGui( void )
    {
        if( this->root_gui )
            delete this->root_gui;
        this->root_gui = 0;
    }

    //sync gui
    void dprender_gui_thread::syncGui( void )
    {
        dpscene_readlock *l;
        dpshared_guard g;
        dpgui *pg;
        dpgui_readlock *gl;

        if( this->root_gui )
            return;

        l = (dpscene_readlock *)dpshared_guard_tryReadLock_timeout( g, this->scn, 30 );
        if( !l )
            return;

        pg = l->getGui();
        if( !pg )
            return;
        gl = (dpgui_readlock *)dpshared_guard_tryReadLock_timeout( g, pg, 100 );
        if( !gl )
            return;

        if( !gl->isRun() )
            return;
        g.release( gl );

        this->root_gui = new dprender_gui( pg );
    }

    //run gui
    void dprender_gui_thread::runGui( dpapi_context_writelock *ctx )
    {
        dprender_gui_writelock *l;
        dpshared_guard g;

        if( !this->root_gui )
            return;

        if( !this->root_gui->isGuiLinked() )
        {
            delete this->root_gui;
            this->root_gui = 0;
        }

        l = (dprender_gui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->root_gui, 30 );
        if( !l )
            return;

        l->passContext( ctx );
        l->run();
    }

    //run input
    void dprender_gui_thread::runInput( void )
    {
        dprender_gui_writelock *l;
        dpshared_guard g;
        dpinput_writelock *il;
        dpinput_event *elist[ 256 ], *pe;
        unsigned int j, i;
        dpapi_readlock *al;
        dpwindow_ref *wr;

        if( !this->inp )
        {
            this->inp = new dpinput();

            al = (dpapi_readlock *)dpshared_guard_tryReadLock_timeout( g, this->apir, 2000 );
            if( al )
            {
                wr = al->getWindow( &g );
                if( wr )
                    this->setSync( wr );

                il = (dpinput_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->inp, 2000 );
                if( il && wr )
                    il->setSync( wr );

                g.release( wr );
                g.release( al );
                g.release( il );
            }
        }

        if( !this->root_gui || !this->inp )
            return;

        l = (dprender_gui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->root_gui, 30 );
        if( !l )
            return;

        il = (dpinput_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->inp, 30 );
        if( !il )
            return;
        il->run();

        j = il->getEvents( elist, 256, this->t_last_inp );
        this->t_last_inp = this->getTicks();

        for( i = 0; i < j; i++ )
        {
            pe = elist[ i ];
            if( pe->h.etype == dpinput_event_type_mouse || pe->h.etype == dpinput_event_type_leftclick || pe->h.etype == dpinput_event_type_rightclick )
            {
                pe->mse.sw = this->lw - this->mw - this->mw;
                pe->mse.sh = this->lh - this->mh - this->mh;
                pe->mse.sx = pe->mse.x / pe->mse.w * this->lw - this->mw;
                pe->mse.sy = pe->mse.y / pe->mse.h * this->lh - this->mh;
            }
            l->processEvent( pe );
        }
    }

    //render gui
    void dprender_gui_thread::renderGui( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        dprender_gui_writelock *l;
        dpshared_guard g;
        dpbitmap_rectangle rc;

        if( !this->root_gui )
            return;

        l = (dprender_gui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->root_gui, 30 );
        if( !l )
            return;
        this->calcMatrix();

        rc.x = 0;
        rc.y = 0;
        rc.w = this->lw - this->mw - this->mw;
        rc.h = this->lh - this->mh - this->mh;

        l->render( &this->mat, &rc, &this->mat, &rc, ctx, cll );
    }

    //compute matrix
    void dprender_gui_thread::calcMatrix( void )
    {
        float sw, sh, rw, rh, r, dw, dh, ss, w, h;

        w = this->w;
        h = this->h;
        sw = 1920.0f;
        sh = 1080.0f;

        ss = sw * sw + sh * sh;
        ss = sqrtf( ss );

        rw = sw / w;
        rh = sh / h;

        r = rw;
        if( r < rh )
            r = rh;

        w = w * r;
        h = h * r;
        dw = w - sw;
        dh = h - sh;
        dw *= 0.5f;
        dh *= 0.5f;

        this->lw = sw + dw + dw;
        this->lh = sh + dh + dh;
        this->mw = dw;
        this->mh = dh;

        this->mat.setOrtho( -dw, sh + dh, 0.0f, sw + dw, -dh, ss );
        this->mat.translate( 0.0f, 0.0f, -0.5f * ss );
        this->undo_mat.inverse( &this->mat );
    }

    //override to handle sync copy, be sure to call base class first!
    void dprender_gui_thread::onSync( dpshared_readlock *psync )
    {
        this->dprender_scene_thread::onSync( psync );

        if( !psync->isSyncType( "dpwindow" ) )
            return;
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dprender_gui_thread::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( s.compare( "dprender_gui_thread" ) == 0 )
            return 1;

        return this->dptask::isSyncType( ctypename );
    }

}








