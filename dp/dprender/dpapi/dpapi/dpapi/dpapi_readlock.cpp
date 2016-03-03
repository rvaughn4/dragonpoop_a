/*
represents the lifecycle of a readlock on a dpapi
this object is returned from a dpapi when readlocked
deleting this object releases the readlock on the dpapi
*/

#include "dpapi_readlock.h"
#include "dpapi.h"

namespace dp
{

    //ctor
    dpapi_readlock::dpapi_readlock( dpapi *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_readlock::~dpapi_readlock( void )
    {

    }

    //returns true if open
    bool dpapi_readlock::isOpen( void )
    {
        return this->p->isOpen();
    }

}







