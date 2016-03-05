
/*

*/

#include "dpapi_opengl1o5.h"
#include "dpapi_opengl1o5_ref.h"
#include "dpapi_opengl1o5_readlock.h"
#include "dpapi_opengl1o5_writelock.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5::dpapi_opengl1o5( dpwindow_factory *wf ) : dpapi( wf )
    {

    }

    //dtor
    dpapi_opengl1o5::~dpapi_opengl1o5( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpapi_opengl1o5::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_opengl1o5_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_opengl1o5::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_opengl1o5_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_opengl1o5::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_opengl1o5_ref( this, k, t_sync );
    }

    //override to init api
    bool dpapi_opengl1o5::initApi( dpwindow_writelock *wl, dpapi_writelock *al )
    {
        return 1;
    }

    //override to run api
    void dpapi_opengl1o5::runApi( dpapi_writelock *al )
    {

    }

    //override to generate rendering context
    dpapi_context *dpapi_opengl1o5::makeContext( dpapi_writelock *al )
    {
        return 0;
    }


}







