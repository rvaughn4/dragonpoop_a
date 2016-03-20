/*
represents the lifecycle of a readlock on a dprender_frame_thread
this object is returned from a dprender_frame_thread when readlocked
deleting this object releases the readlock on the dprender_frame_thread
*/

#include "dprender_frame_thread_readlock.h"
#include "dprender_frame_thread.h"

namespace dp
{

    //ctor
    dprender_frame_thread_readlock::dprender_frame_thread_readlock( dprender_frame_thread *p, dpmutex_readlock *ml ) : dptask_readlock( p, ml )
    {

    }

    //dtor
    dprender_frame_thread_readlock::~dprender_frame_thread_readlock( void )
    {

    }

}











