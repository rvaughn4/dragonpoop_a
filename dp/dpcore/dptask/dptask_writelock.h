/*
represents the lifecycle of a writelock on a dptask
this object is returned from a dptask when writelocked
deleting this object releases the writelock on the dptask
*/

#ifndef dptask_writelock_h
#define dptask_writelock_h

#include "dptask_defines.h"
#include "../dpshared/dpshared_writelock.h"

namespace dp
{

    class dptask;
    class dpmutex_writelock;
    class dptask_ref;
    class dpthread_writelock;

    class dptask_writelock : public dpshared_writelock
    {

    private:

        dptask *p;

    protected:

        //dtor
        virtual ~dptask_writelock( void );

    public:

        //ctor
        dptask_writelock( dptask *p, dpmutex_writelock *ml );
        //run task
        void run( dpthread_writelock *thdl );
        //returns true if running
        bool isRun( void );
        //stops task
        void stop( void );

    };

}

#endif





