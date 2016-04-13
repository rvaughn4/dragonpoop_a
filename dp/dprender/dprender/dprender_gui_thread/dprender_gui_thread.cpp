
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

#include "../../../dpgfx/dpscene/dpscene_readlock.h"
#include "../../../dpgfx/dpscene/dpscene_ref.h"

#include "../../../dpdefines.h"

#include "../../dprender_gui/dprender_gui/dprender_gui.h"
#include "../../dprender_gui/dprender_gui/dprender_gui_writelock.h"


namespace dp
{

    //ctor
    dprender_gui_thread::dprender_gui_thread( dpscene_ref *scn, dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b ) : dprender_scene_thread( ctx, cl_a, cl_b, flag_a, flag_b )
    {
        this->root_gui = 0;
        this->scn = (dpscene_ref *)this->g.getRef( scn );
    }

    //dtor
    dprender_gui_thread::~dprender_gui_thread( void )
    {
        this->waitForStop();
        this->deleteGui();
        this->unlink();
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

        if( this->root_gui )
            return;

        l = (dpscene_readlock *)dpshared_guard_tryReadLock_timeout( g, this->scn, 30 );
        if( !l )
            return;

        pg = l->getGui();
        if( !pg )
            return;

        this->root_gui = new dprender_gui( pg );
    }

    //run gui
    void dprender_gui_thread::runGui( dpapi_context_writelock *ctx )
    {
        dprender_gui_writelock *l;
        dpshared_guard g;

        if( !this->root_gui )
            return;

        l = (dprender_gui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->root_gui, 30 );
        if( !l )
            return;
        l->passContext( ctx );
        l->run();
    }

    //render gui
    void dprender_gui_thread::renderGui( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        dprender_gui_writelock *l;
        dpshared_guard g;

        if( !this->root_gui )
            return;

        l = (dprender_gui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->root_gui, 30 );
        if( !l )
            return;
        l->render( 0, ctx, cll );
    }

    //compute matrix
    void dprender_gui_thread::calcMatrix( void )
    {

    }

}








