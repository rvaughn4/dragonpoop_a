
/*

*/

#include "dpapi_texture.h"
#include "dpapi_texture_ref.h"
#include "dpapi_texture_readlock.h"
#include "dpapi_texture_writelock.h"

namespace dp
{

    //ctor
    dpapi_texture::dpapi_texture( dpapi_context_writelock *ctx, dpbitmap_32bit_uncompressed *bm )
    {

    }

    //dtor
    dpapi_texture::~dpapi_texture( void )
    {
        this->unlink();
    }

    //generate readlock
    dpshared_readlock *dpapi_texture::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_texture_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_texture::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_texture_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_texture::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_texture_ref( this, k, t_sync );
    }

}









