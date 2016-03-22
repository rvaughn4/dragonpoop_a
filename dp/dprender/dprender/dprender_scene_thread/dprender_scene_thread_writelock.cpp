/*
represents the lifecycle of a writelock on a dprender_scene_thread
this object is returned from a dprender_scene_thread when writelocked
deleting this object releases the writelock on the dprender_scene_thread
*/

#include "dprender_scene_thread_writelock.h"
#include "dprender_scene_thread.h"

namespace dp
{

    //ctor
    dprender_scene_thread_writelock::dprender_scene_thread_writelock( dprender_scene_thread *p, dpmutex_writelock *ml ) : dptask_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_scene_thread_writelock::~dprender_scene_thread_writelock( void )
    {

    }

}













