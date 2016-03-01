/*
represents the lifecycle of a writelock on a dpwindow
this object is returned from a dpwindow when writelocked
deleting this object releases the writelock on the dpwindow
*/

#ifndef dpwindow_x11_writelock_h
#define dpwindow_x11_writelock_h

#include "../dpwindow/dpwindow_writelock.h"

namespace dp
{

    class dpwindow_x11;

    class dpwindow_x11_writelock : public dpwindow_writelock
    {

    private:

        dpwindow_x11 *p;

    protected:

        //dtor
        virtual ~dpwindow_x11_writelock( void );

    public:

        //ctor
        dpwindow_x11_writelock( dpwindow_x11 *p, dpmutex_writelock *ml );

    };

}

#endif







