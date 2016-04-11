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
    dprender_scene_writelock::dprender_scene_writelock( dprender_scene *p, dpmutex_writelock *ml ) : dptask_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_scene_writelock::~dprender_scene_writelock( void )
    {

    }

    //draw scene
    bool dprender_scene_writelock::draw( dpapi_context_writelock *ctxl, dpapi_primary_commandlist_writelock *cll )
    {
        return this->p->draw( this, ctxl, cll );
    }

    //purge tasks and all api stuff so that api can be deleted
    void dprender_scene_writelock::purgeAll( void )
    {
        this->p->purgeAll();
    }

}










