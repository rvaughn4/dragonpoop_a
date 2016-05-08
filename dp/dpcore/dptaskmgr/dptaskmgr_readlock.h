 /*
represents the lifecycle of a readlock on a dptaskmgrmgr
this object is returned from a dptaskmgr when readlocked
deleting this object releases the readlock on the dptaskmgr
*/

#ifndef dptaskmgr_readlock_h
#define dptaskmgr_readlock_h

#include "../dptask/dptask_readlock.h"
#include <string>

namespace dp
{

    class dptaskmgr;
    class dpmutex_readlock;
    class dptaskmgr_ref;

    class dptaskmgr_readlock : public dptask_readlock
    {

        dptaskmgr *p;

    private:

    protected:

        //dtor
        virtual ~dptaskmgr_readlock( void );

    public:

        //ctor
        dptaskmgr_readlock( dptaskmgr *p, dpmutex_readlock *ml );
        //get task manager summary text listing all threads and tasks
        void getSummary( std::string *s );

    };

}

#endif





