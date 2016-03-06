 /*
represents the lifecycle of a writelock on a dpapi_commandlist
this object is returned from a dpapi_commandlist when writelocked
deleting this object releases the writelock on the dpapi_commandlist
*/

#include "dpapi_commandlist_writelock.h"
#include "dpapi_commandlist.h"

namespace dp
{

    //ctor
    dpapi_commandlist_writelock::dpapi_commandlist_writelock( dpapi_commandlist *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_commandlist_writelock::~dpapi_commandlist_writelock( void )
    {

    }

}










