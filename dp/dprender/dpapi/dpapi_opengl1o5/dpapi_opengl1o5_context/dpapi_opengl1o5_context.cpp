
/*

*/

#include "dpapi_opengl1o5_context.h"
#include "dpapi_opengl1o5_context_ref.h"
#include "dpapi_opengl1o5_context_readlock.h"
#include "dpapi_opengl1o5_context_writelock.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_context::dpapi_opengl1o5_context( dpapi_writelock *awl ) : dpapi_context( awl )
    {

    }

    //dtor
    dpapi_opengl1o5_context::~dpapi_opengl1o5_context( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_opengl1o5_context::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_opengl1o5_context_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_opengl1o5_context::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_opengl1o5_context_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_opengl1o5_context::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_opengl1o5_context_ref( this, k, t_sync );
    }

    //generate renderpass
    dpapi_renderpass *dpapi_opengl1o5_context::makeRenderpass( dpapi_opengl1o5_context_writelock *l )
    {
        return 0;
    }

}








