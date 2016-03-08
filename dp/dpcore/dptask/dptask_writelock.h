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
    class dpthread;
    class dptaskmgr;
    class dpthread_ref;
    class dptaskmgr_ref;
    class dpthread_writelock;
    class dptaskmgr_writelock;

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
        //returns true if running
        bool isRun( void );
        //stops task
        void stop( void );
        //return ms delay
        unsigned int getDelay( void );
        //set delay
        void setDelay( unsigned int ms );
        //set thread that owns task
        void setOwnerThread( dpthread *t );
        //set thread that owns task
        void setOwnerThread( dpthread_writelock *t );
        //set thread that owns task
        void setOwnerThread( dpthread_ref *t );
        //set task manager that owns task
        void setOwnerTaskManager( dptaskmgr *t );
        //set task manager that owns task
        void setOwnerTaskManager( dptaskmgr_writelock *t );
        //set task manager that owns task
        void setOwnerTaskManager( dptaskmgr_ref *t );

    };

}

#endif





