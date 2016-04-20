/*
represents the lifecycle of a readlock on a dpinput
this object is returned from a dpinput when readlocked
deleting this object releases the readlock on the dpinput
*/

#include "dpinput_readlock.h"

namespace dp
{

    //ctor
    dpinput_readlock::dpinput_readlock( dpinput *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpinput_readlock::~dpinput_readlock( void )
    {

    }

    //get events newer than time
    unsigned int dpinput_readlock::getEvents( dpinput_event **elist, unsigned int max_sz, uint64_t t )
    {
        return this->p->getEvents( elist, max_sz, t );
    }

}







