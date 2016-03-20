/*
represents the lifecycle of a writelock on a dprender_scene
this object is returned from a dprender_scene when writelocked
deleting this object releases the writelock on the dprender_scene
*/

#include "dprender_scene_writelock.h"
#include "dprender_scene.h"

namespace dp
{

    //ctor
    dprender_scene_writelock::dprender_scene_writelock( dprender_scene *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_scene_writelock::~dprender_scene_writelock( void )
    {

    }

    //attach scene to renderer
    bool dprender_scene_writelock::attach( dpapi_writelock *apil, dprender_writelock *rl, dprender_frame_thread_writelock *tl )
    {
        return this->p->attach( apil, rl, tl );
    }

}










