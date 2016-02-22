/*
represents the lifecycle of a writelock on a dpthread
this object is returned from a dpthread when writelocked
deleting this object releases the writelock on the dpthread
*/

#ifndef dpthread_writelock_h
#define dpthread_writelock_h

#include "dpthread_defines.h"
#include "../dpshared/dpshared_writelock.h"

namespace dp
{

    class dpthread;
    class dpmutex_writelock;
    class dpthread_ref;
    class dptask;
    class dptask_ref;
    class dptask_readlock;
    class dptask_writelock;

    class dpthread_writelock : public dpshared_writelock
    {

    private:

        dpthread *p;

    protected:

        //dtor
        virtual ~dpthread_writelock( void );

    public:

        //ctor
        dpthread_writelock( dpthread *p, dpmutex_writelock *ml );
        //returns true if should run
        bool doRun( void );
        //returns true if running
        bool isRunning( void );
        //return thread delay time
        unsigned int getDelay( void );
        //add a static task to task list
        bool addStaticTask( dptask *t, unsigned int weight );
        //add a static task to task list
        bool addStaticTask( dptask_ref *t, unsigned int weight );
        //add a static task to task list
        bool addStaticTask( dptask_readlock *t, unsigned int weight );
        //add a static task to task list
        bool addStaticTask( dptask_writelock *t, unsigned int weight );
        //add a dynamic task to task list
        bool addDynamicTask( dptask *t );
        //add a dynamic task to task list
        bool addDynamicTask( dptask_ref *t );
        //add a dynamic task to task list
        bool addDynamicTask( dptask_readlock *t );
        //add a dynamic task to task list
        bool addDynamicTask( dptask_writelock *t );

    };

}

#endif




