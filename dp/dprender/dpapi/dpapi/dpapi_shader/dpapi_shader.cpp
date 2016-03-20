
/*

*/

#include "dpapi_shader.h"
#include "dpapi_shader_ref.h"
#include "dpapi_shader_readlock.h"
#include "dpapi_shader_writelock.h"

namespace dp
{

    //ctor
    dpapi_shader::dpapi_shader( dpapi_context_writelock *ctx )
    {

    }

    //dtor
    dpapi_shader::~dpapi_shader( void )
    {
        this->unlink();
    }

    //generate readlock
    dpshared_readlock *dpapi_shader::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_shader_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_shader::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_shader_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_shader::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_shader_ref( this, k, t_sync );
    }

}









