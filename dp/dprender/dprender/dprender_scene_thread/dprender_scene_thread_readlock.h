/*
represents the lifecycle of a readlock on a dprender_scene_thread
this object is returned from a dprender_scene_thread when readlocked
deleting this object releases the readlock on the dprender_scene_thread
*/

#ifndef dprender_scene_thread_readlock_h
#define dprender_scene_thread_readlock_h

#include "../../../dpcore/dptask/dptask_readlock.h"

namespace dp
{

    class dprender_scene_thread;

    class dprender_scene_thread_readlock : public dptask_readlock
    {

        dprender_scene_thread *p;

    private:

    protected:

        //dtor
        virtual ~dprender_scene_thread_readlock( void );

    public:

        //ctor
        dprender_scene_thread_readlock( dprender_scene_thread *p, dpmutex_readlock *ml );

    };

}

#endif









