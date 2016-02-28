/*
represents the lifecycle of a readlock on a dpwindow
this object is returned from a dpwindow when readlocked
deleting this object releases the readlock on the dpwindow
*/

#ifndef dpwindow_readlock_h
#define dpwindow_readlock_h

#include "../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpwindow;
    class dpmutex_readlock;
    class dpwindow_ref;

    class dpwindow_readlock : public dpshared_readlock
    {

        dpwindow *p;

    private:

    protected:

        //dtor
        virtual ~dpwindow_readlock( void );

    public:

        //ctor
        dpwindow_readlock( dpwindow *p, dpmutex_readlock *ml );

    };

}

#endif





