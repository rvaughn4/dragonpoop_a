/*
represents the lifecycle of a readlock on a dprender_scene_thread
this object is returned from a dprender_scene_thread when readlocked
deleting this object releases the readlock on the dprender_scene_thread
*/

#include "dprender_scene_thread_readlock.h"
#include "dprender_scene_thread.h"

namespace dp
{

    //ctor
    dprender_scene_thread_readlock::dprender_scene_thread_readlock( dprender_scene_thread *p, dpmutex_readlock *ml ) : dptask_readlock( p, ml )
    {

    }

    //dtor
    dprender_scene_thread_readlock::~dprender_scene_thread_readlock( void )
    {

    }

}












