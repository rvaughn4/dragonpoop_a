/*
represents the lifecycle of a readlock on a dptask
this object is returned from a dptask when readlocked
deleting this object releases the readlock on the dptask
*/

#ifndef dptask_readlock_h
#define dptask_readlock_h

#include "dptask_defines.h"
#include "../dpshared/dpshared_readlock.h"

namespace dp
{

    class dptask;
    class dpmutex_readlock;
    class dptask_ref;

    class dptask_readlock : public dpshared_readlock
    {

        dptask *p;

    private:

    protected:

        //dtor
        virtual ~dptask_readlock( void );

    public:

        //ctor
        dptask_readlock( dptask *p, dpmutex_readlock *ml );

    };

}

#endif




