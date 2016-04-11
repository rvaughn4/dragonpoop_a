/*
represents the lifecycle of a writelock on a dprender_frame_thread
this object is returned from a dprender_frame_thread when writelocked
deleting this object releases the writelock on the dprender_frame_thread
*/

#include "dprender_frame_thread_writelock.h"
#include "dprender_frame_thread.h"

namespace dp
{

    //ctor
    dprender_frame_thread_writelock::dprender_frame_thread_writelock( dprender_frame_thread *p, dpmutex_writelock *ml ) : dptask_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_frame_thread_writelock::~dprender_frame_thread_writelock( void )
    {

    }

    //add scene
    bool dprender_frame_thread_writelock::addScene( dprender_scene *s )
    {
        return this->p->addScene( s );
    }

    //remove scene
    bool dprender_frame_thread_writelock::removeScene( dprender_scene *s )
    {
        return this->p->removeScene( s );
    }

}












