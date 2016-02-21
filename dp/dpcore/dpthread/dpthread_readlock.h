/*
represents the lifecycle of a readlock on a dpthread
this object is returned from a dpthread when readlocked
deleting this object releases the readlock on the dpthread
*/

#ifndef dpthread_readlock_h
#define dpthread_readlock_h

#include "dpthread_defines.h"
#include "../dpshared/dpshared_readlock.h"

namespace dp
{

    class dpthread;
    class dpmutex_readlock;
    class dpthread_ref;

    class dpthread_readlock : public dpshared_readlock
    {

        dpthread *p;

    private:

    protected:

    public:

        //ctor
        dpthread_readlock( dpthread *p, dpmutex_readlock *ml );
        //dtor
        virtual ~dpthread_readlock( void );

    };

}

#endif



