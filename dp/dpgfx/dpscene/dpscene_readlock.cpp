/*
*/

#include "dpscene_readlock.h"
#include "dpscene.h"

namespace dp
{

    //ctor
    dpscene_readlock::dpscene_readlock( dpscene *p, dpmutex_readlock *ml ) : dptask_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpscene_readlock::~dpscene_readlock( void )
    {

    }

}






