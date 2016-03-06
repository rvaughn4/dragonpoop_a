
/*

*/

#include "dpapi_commandlist.h"
#include "dpapi_commandlist_ref.h"
#include "dpapi_commandlist_readlock.h"
#include "dpapi_commandlist_writelock.h"

namespace dp
{

    //ctor
    dpapi_commandlist::dpapi_commandlist( dpapi_context_writelock *awl ) : dpshared()
    {

    }

    //dtor
    dpapi_commandlist::~dpapi_commandlist( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_commandlist::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_commandlist_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_commandlist::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_commandlist_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_commandlist::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_commandlist_ref( this, k, t_sync );
    }

}








