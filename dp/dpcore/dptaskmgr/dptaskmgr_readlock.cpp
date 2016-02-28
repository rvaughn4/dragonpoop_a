 /*
represents the lifecycle of a readlock on a dptaskmgrmgr
this object is returned from a dptaskmgr when readlocked
deleting this object releases the readlock on the dptaskmgr
*/

#include "dptaskmgr_readlock.h"
#include "dptaskmgr.h"

namespace dp
{

    //ctor
    dptaskmgr_readlock::dptaskmgr_readlock( dptaskmgr *p, dpmutex_readlock *ml ) : dptask_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dptaskmgr_readlock::~dptaskmgr_readlock( void )
    {

    }

}






