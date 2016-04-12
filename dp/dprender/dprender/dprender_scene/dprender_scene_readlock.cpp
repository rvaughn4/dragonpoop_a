/*
represents the lifecycle of a readlock on a dprender_scene
this object is returned from a dprender_scene when readlocked
deleting this object releases the readlock on the dprender_scene
*/

#include "dprender_scene_readlock.h"
#include "dprender_scene.h"

namespace dp
{

    //ctor
    dprender_scene_readlock::dprender_scene_readlock( dprender_scene *p, dpmutex_readlock *ml ) : dptask_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_scene_readlock::~dprender_scene_readlock( void )
    {

    }

    //returns true if belongs to scene
    bool dprender_scene_readlock::hasScene( dpscene *scn )
    {
        return this->p->hasScene( scn );
    }

    //returns true if scene is ready
    bool dprender_scene_readlock::isReady( void )
    {
        return this->p->isReady();
    }

}











