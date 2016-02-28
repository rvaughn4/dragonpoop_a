 /*
represents the lifecycle of a readlock on a dpgfx
this object is returned from a dpgfx when readlocked
deleting this object releases the readlock on the dpgfx
*/

#include "dpgfx_readlock.h"
#include "dpgfx.h"

namespace dp
{

    //ctor
    dpgfx_readlock::dpgfx_readlock( dpgfx *p, dpmutex_readlock *ml ) : dptask_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpgfx_readlock::~dpgfx_readlock( void )
    {

    }

}







