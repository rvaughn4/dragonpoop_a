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

    }

    //dtor
    dprender_scene_writelock::~dprender_scene_writelock( void )
    {

    }

}










