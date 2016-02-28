/*
represents the lifecycle of a writelock on a dptaskmgr
this object is returned from a dptaskmgr when writelocked
deleting this object releases the writelock on the dptaskmgr
*/

#ifndef dptaskmgr_writelock_h
#define dptaskmgr_writelock_h

#include "../dptask/dptask_writelock.h"

namespace dp
{

    class dptaskmgr;
    class dpmutex_writelock;
    class dptaskmgr_ref;
    class dpthread_writelock;
    class dptask;
    class dptask_ref;
    class dptask_readlock;
    class dptask_writelock;

    class dptaskmgr_writelock : public dptask_writelock
    {

    private:

        dptaskmgr *p;

    protected:

        //dtor
        virtual ~dptaskmgr_writelock( void );

    public:

        //ctor
        dptaskmgr_writelock( dptaskmgr *p, dpmutex_writelock *ml );
        //add static task
        bool addStaticTask( dptask *t, unsigned int weight );
        //add static task
        bool addStaticTask( dptask_ref *t, unsigned int weight );
        //add static task
        bool addStaticTask( dptask_readlock *t, unsigned int weight );
        //add static task
        bool addStaticTask( dptask_writelock *t, unsigned int weight );
        //add dynamic task
        bool addDynamicTask( dptask *t );
        //add dynamic task
        bool addDynamicTask( dptask_ref *t );
        //add dynamic task
        bool addDynamicTask( dptask_readlock *t );
        //add dynamic task
        bool addDynamicTask( dptask_writelock *t );

    };

}

#endif






