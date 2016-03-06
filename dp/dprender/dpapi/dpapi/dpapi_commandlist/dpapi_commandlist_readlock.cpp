 /*
represents the lifecycle of a readlock on a dpapi_commandlist
this object is returned from a dpapi_commandlist when readlocked
deleting this object releases the readlock on the dpapi_commandlist
*/

#include "dpapi_commandlist_readlock.h"
#include "dpapi_commandlist.h"

namespace dp
{

    //ctor
    dpapi_commandlist_readlock::dpapi_commandlist_readlock( dpapi_commandlist *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_commandlist_readlock::~dpapi_commandlist_readlock( void )
    {

    }

}











