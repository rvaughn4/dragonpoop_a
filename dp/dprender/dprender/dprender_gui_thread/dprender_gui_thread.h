
/*

*/

#ifndef dprender_gui_thread_h
#define dprender_gui_thread_h

#include "../dprender_scene_thread/dprender_scene_thread.h"
#include "../../../dpgfx/dpmatrix/dpmatrix.h"

namespace dp
{
    class dprender_gui;
    class dpscene_ref;
    class dpgui;
    class dpinput;

    class dprender_gui_thread : public dprender_scene_thread
    {

    private:

        dpscene_ref *scn;
        dprender_gui *root_gui;
        dpshared_guard g;
        unsigned int w, h;
        dpmatrix mat, undo_mat;
        dpinput *inp;
        uint64_t t_last_inp;

        //delete gui
        void deleteGui( void );
        //sync gui
        void syncGui( void );
        //run gui
        void runGui( dpapi_context_writelock *ctx );
        //render gui
        void renderGui( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll );
        //compute matrix
        void calcMatrix( void );
        //run input
        void runInput( void );

    protected:

        //override to handle scene start
        virtual bool onSceneStart( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx );
        //override to handle scene stop/cleanup
        virtual bool onSceneStop( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx );
        //override to handle scene render
        virtual bool onSceneRender( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll );
        //override to handle sync copy, be sure to call base class first!
        virtual void onSync( dpshared_readlock *psync );
        //override to test type for safe syncing, be sure to call base class first!
        virtual bool isSyncType( const char *ctypename );

    public:

        //ctor
        dprender_gui_thread( dpapi_ref *api, dpscene_ref *scn, dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b );
        //dtor
        virtual ~dprender_gui_thread( void );

    };

}

#endif







