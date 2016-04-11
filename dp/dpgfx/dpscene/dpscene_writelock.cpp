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

    //return root gui
    dpgui *dpscene_writelock::getGui( void )
    {
        return this->p->getGui();
    }

}







