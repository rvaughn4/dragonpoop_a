
/*

*/

#ifndef dprender_hello_triangle_scene_thread_h
#define dprender_hello_triangle_scene_thread_h

#include "../dprender_scene_thread/dprender_scene_thread.h"

namespace dp
{

    class dpapi_vertexbuffer;
    class dpapi_indexbuffer;
    class dpapi_bundle;

    class dprender_hello_triangle_scene_thread : public dprender_scene_thread
    {

    private:

        dpapi_vertexbuffer *vb;
        dpapi_indexbuffer *ib;
        dpapi_bundle *bdle;

    protected:

        //override to handle scene start
        virtual bool onSceneStart( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx );
        //override to handle scene stop/cleanup
        virtual bool onSceneStop( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx );
        //override to handle scene render
        virtual bool onSceneRender( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll );

    public:

        //ctor
        dprender_hello_triangle_scene_thread( dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b );
        //dtor
        virtual ~dprender_hello_triangle_scene_thread( void );

    };

}

#endif







