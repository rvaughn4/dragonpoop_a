/*
*/

#include "dpscene_writelock.h"
#include "dpscene.h"

namespace dp
{

    //ctor
    dpscene_writelock::dpscene_writelock( dpscene *p, dpmutex_writelock *ml ) : dptask_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpscene_writelock::~dpscene_writelock( void )
    {

    }

}







