/*
represents the lifecycle of a writelock on a dpgfx
this object is returned from a dpgfx when writelocked
deleting this object releases the writelock on the dpgfx
*/

#include "dpgfx_writelock.h"
#include "dpgfx.h"

namespace dp
{

    //ctor
    dpgfx_writelock::dpgfx_writelock( dpgfx *p, dpmutex_writelock *ml ) : dptask_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpgfx_writelock::~dpgfx_writelock( void )
    {

    }

}








