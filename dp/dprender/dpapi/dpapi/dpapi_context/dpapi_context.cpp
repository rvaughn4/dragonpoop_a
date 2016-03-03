
/*

*/

#include "dpapi_context.h"
#include "dpapi_context_ref.h"
#include "dpapi_context_readlock.h"
#include "dpapi_context_writelock.h"

namespace dp
{

    //ctor
    dpapi_context::dpapi_context( dpapi_writelock *awl ) : dpshared()
    {

    }

    //dtor
    dpapi_context::~dpapi_context( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_context::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_context_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_context::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_context_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_context::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_context_ref( this, k, t_sync );
    }

    //override to handle sync copy, be sure to call base class first!
    void dpapi_context::onSync( dpshared_readlock *psync )
    {
        this->dpshared::onSync( psync );
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dpapi_context::isSyncType( const char *ctypename )
    {
        if( this->dpshared::isSyncType( ctypename ) )
            return 1;

        return 0;
    }

    //override to handle processing
    void dpapi_context::onRun( dpshared_writelock *wl )
    {

    }

}







