
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

#include "../../dprender_gui/dprender_gui/dprender_gui.h"
#include "../../dprender_gui/dprender_gui/dprender_gui_writelock.h"


namespace dp
{

    //ctor
    dprender_gui_thread::dprender_gui_thread( dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b ) : dprender_scene_thread( ctx, cl_a, cl_b, flag_a, flag_b )
    {
        this->root_gui = 0;
    }

    //dtor
    dprender_gui_thread::~dprender_gui_thread( void )
    {
        this->waitForStop();
        this->unlink();

        if( this->root_gui )
            delete this->root_gui;
    }

    //override to handle scene start
    bool dprender_gui_thread::onSceneStart( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx )
    {
        return 1;
    }

    //override to handle scene stop/cleanup
    bool dprender_gui_thread::onSceneStop( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx )
    {
        if( this->root_gui )
            delete this->root_gui;
        this->root_gui = 0;

        return 1;
    }

    //override to handle scene render
    bool dprender_gui_thread::onSceneRender( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        dpshared_guard g;
        dprender_gui_writelock *gl;

        gl = (dprender_gui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->root_gui, 30 );
        if( gl )
        {
            gl->passContext( ctx );
            gl->run();
            //
        }

        return 1;
    }

}








