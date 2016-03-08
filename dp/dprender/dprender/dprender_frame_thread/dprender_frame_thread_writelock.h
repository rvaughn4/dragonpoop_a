/*
represents the lifecycle of a writelock on a dprender_frame_thread
this object is returned from a dprender_frame_thread when writelocked
deleting this object releases the writelock on the dprender_frame_thread
*/

#ifndef dprender_frame_thread_writelock_h
#define dprender_frame_thread_writelock_h

#include "../../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dprender_frame_thread;

    class dprender_frame_thread_writelock : public dptask_writelock
    {

        dprender_frame_thread *p;

    private:

    protected:

        //dtor
        virtual ~dprender_frame_thread_writelock( void );

    public:

        //ctor
        dprender_frame_thread_writelock( dprender_frame_thread *p, dpmutex_writelock *ml );

    };

}

#endif








