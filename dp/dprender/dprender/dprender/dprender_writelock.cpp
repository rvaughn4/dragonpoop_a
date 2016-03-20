/*
represents the lifecycle of a writelock on a dprender
this object is returned from a dprender when writelocked
deleting this object releases the writelock on the dprender
*/

#include "dprender_writelock.h"
#include "dprender.h"

namespace dp
{

    //ctor
    dprender_writelock::dprender_writelock( dprender *p, dpmutex_writelock *ml ) : dptask_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_writelock::~dprender_writelock( void )
    {

    }

    //add scene
    bool dprender_writelock::addScene( dprender_scene *s )
    {
        return this->p->addScene( s, this );
    }

    //remove scene
    void dprender_writelock::removeScene( dprender_scene *s )
    {
        this->p->removeScene( s, this );
    }

}









