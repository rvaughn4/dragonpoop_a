
/*
*/

#include "dpbuffer_shared.h"
#include "dpbuffer_shared_ref.h"
#include "dpbuffer_shared_readlock.h"
#include "dpbuffer_shared_writelock.h"

namespace dp
{

    //ctor
    dpbuffer_shared::dpbuffer_shared( dpbuffer *b ) : dpbuffer_wrapper( b ), dpshared()
    {

    }

    //dtor
    dpbuffer_shared::~dpbuffer_shared( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpbuffer_shared::genReadLock( dpmutex_readlock *ml )
    {
        return new dpbuffer_shared_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpbuffer_shared::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpbuffer_shared_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpbuffer_shared::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpbuffer_shared_ref( this, k, t_sync );
    }

}



