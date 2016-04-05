
/*

*/

#ifndef dprender_gui_thread_h
#define dprender_gui_thread_h

#include "../dprender_scene_thread/dprender_scene_thread.h"

namespace dp
{
    class dprender_gui;

    class dprender_gui_thread : public dprender_scene_thread
    {

    private:

        dprender_gui *root_gui;

    protected:

        //override to handle scene start
        virtual bool onSceneStart( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx );
        //override to handle scene stop/cleanup
        virtual bool onSceneStop( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx );
        //override to handle scene render
        virtual bool onSceneRender( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll );

    public:

        //ctor
        dprender_gui_thread( dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b );
        //dtor
        virtual ~dprender_gui_thread( void );

    };

}

#endif







