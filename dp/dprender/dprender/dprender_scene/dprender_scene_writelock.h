/*
represents the lifecycle of a writelock on a dprender_scene
this object is returned from a dprender_scene when writelocked
deleting this object releases the writelock on the dprender_scene
*/

#ifndef dprender_scene_writelock_h
#define dprender_scene_writelock_h

#include "../../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dprender_scene;
    class dpapi_writelock;
    class dprender_writelock;
    class dprender_frame_thread_writelock;
    class dpapi_context_writelock;
    class dpapi_primary_commandlist_writelock;
    class dpscene;

    class dprender_scene_writelock : public dptask_writelock
    {

        dprender_scene *p;

    private:

    protected:

        //dtor
        virtual ~dprender_scene_writelock( void );

    public:

        //ctor
        dprender_scene_writelock( dprender_scene *p, dpmutex_writelock *ml );
        //draw scene
        bool draw( dpapi_context_writelock *ctxl, dpapi_primary_commandlist_writelock *cll );
        //returns true if belongs to scene
        bool hasScene( dpscene *scn );
        //returns true if scene is ready
        bool isReady( void );

    };

}

#endif









