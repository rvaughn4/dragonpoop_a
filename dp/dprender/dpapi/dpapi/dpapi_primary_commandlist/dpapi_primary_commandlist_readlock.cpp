 /*
represents the lifecycle of a readlock on a dpapi_primary_commandlist
this object is returned from a dpapi_primary_commandlist when readlocked
deleting this object releases the readlock on the dpapi_primary_commandlist
*/

#include "dpapi_primary_commandlist_readlock.h"
#include "dpapi_primary_commandlist.h"

namespace dp
{

    //ctor
    dpapi_primary_commandlist_readlock::dpapi_primary_commandlist_readlock( dpapi_primary_commandlist *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpapi_primary_commandlist_readlock::~dpapi_primary_commandlist_readlock( void )
    {

    }

}












