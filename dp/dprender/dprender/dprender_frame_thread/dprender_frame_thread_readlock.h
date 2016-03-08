/*
represents the lifecycle of a readlock on a dprender_frame_thread
this object is returned from a dprender_frame_thread when readlocked
deleting this object releases the readlock on the dprender_frame_thread
*/

#ifndef dprender_frame_thread_readlock_h
#define dprender_frame_thread_readlock_h

#include "../../../dpcore/dptask/dptask_readlock.h"

namespace dp
{

    class dprender_frame_thread;

    class dprender_frame_thread_readlock : public dptask_readlock
    {

        dprender_frame_thread *p;

    private:

    protected:

        //dtor
        virtual ~dprender_frame_thread_readlock( void );

    public:

        //ctor
        dprender_frame_thread_readlock( dprender_frame_thread *p, dpmutex_readlock *ml );

    };

}

#endif







