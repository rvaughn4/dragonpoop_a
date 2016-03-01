/*
represents the lifecycle of a readlock on a dpwindow
this object is returned from a dpwindow when readlocked
deleting this object releases the readlock on the dpwindow
*/

#ifndef dpwindow_x11_readlock_h
#define dpwindow_x11_readlock_h

#include "../dpwindow/dpwindow_readlock.h"

namespace dp
{

    class dpwindow_x11;

    class dpwindow_x11_readlock : public dpwindow_readlock
    {

        dpwindow_x11 *p;

    private:

    protected:

        //dtor
        virtual ~dpwindow_x11_readlock( void );

    public:

        //ctor
        dpwindow_x11_readlock( dpwindow_x11 *p, dpmutex_readlock *ml );

        friend class dpwindow_x11;
    };

}

#endif






