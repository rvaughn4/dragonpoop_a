/*
represents the lifecycle of a writelock on a dprender_scene
this object is returned from a dprender_scene when writelocked
deleting this object releases the writelock on the dprender_scene
*/

#ifndef dprender_scene_writelock_h
#define dprender_scene_writelock_h

#include "../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dprender_scene;
    class dpapi_writelock;
    class dprender_writelock;
    class dprender_frame_thread_writelock;

    class dprender_scene_writelock : public dpshared_writelock
    {

        dprender_scene *p;

    private:

    protected:

        //dtor
        virtual ~dprender_scene_writelock( void );

    public:

        //ctor
        dprender_scene_writelock( dprender_scene *p, dpmutex_writelock *ml );
        //attach scene to renderer
        bool attach( dpapi_writelock *apil, dprender_writelock *rl, dprender_frame_thread_writelock *tl );

    };

}

#endif









