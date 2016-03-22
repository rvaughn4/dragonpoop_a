/*
represents the lifecycle of a readlock on a dprender_scene_thread
this object is returned from a dprender_scene_thread when writelocked
deleting this object releases the writelock on the dprender_scene_thread
*/

#ifndef dprender_scene_thread_writelock_h
#define dprender_scene_thread_writelock_h

#include "../../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dprender_scene_thread;
    class dprender_scene;
    class dprender_writelock;
    class dpapi_writelock;

    class dprender_scene_thread_writelock : public dptask_writelock
    {

        dprender_scene_thread *p;

    private:

    protected:

        //dtor
        virtual ~dprender_scene_thread_writelock( void );

    public:

        //ctor
        dprender_scene_thread_writelock( dprender_scene_thread *p, dpmutex_writelock *ml );

    };

}

#endif










