
/*

*/

#include "dpapi_opengl1o5_texture.h"
#include "dpapi_opengl1o5_texture_ref.h"
#include "dpapi_opengl1o5_texture_readlock.h"
#include "dpapi_opengl1o5_texture_writelock.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_writelock.h"
#include "../../../../dpgfx/dpbitmap/dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_texture::dpapi_opengl1o5_texture( dpapi_opengl1o5_context_writelock *ctx, dpbitmap *bm ) : dpapi_texture( ctx, bm )
    {
        dpbitmap_32bit_uncompressed b( bm->getWidth(), bm->getHeight() );
        dpbuffer_static bs;

        this->gltex = 0;

        ctx->makeActive();
        b.copy( bm );

        if( !b.getPixelData( &bs ) )
            return;

        this->gl->glGenTextures( 1, &this->gltex );
        if( !this->gltex )
            return;

        this->gl->glBindTexture( opengl1o5_lib_TEXTURE_2D, this->gltex );

        this->gl->glTexParameteri( opengl1o5_lib_TEXTURE_2D, opengl1o5_lib_TEXTURE_MIN_FILTER, opengl1o5_lib_LINEAR );
        this->gl->glTexParameteri( opengl1o5_lib_TEXTURE_2D, opengl1o5_lib_TEXTURE_MAG_FILTER, opengl1o5_lib_LINEAR );

        this->gl->glTexImage2D( opengl1o5_lib_TEXTURE_2D, 0, opengl1o5_lib_RGBA, b.getWidth(), b.getHeight(), 0, opengl1o5_lib_RGBA, opengl1o5_lib_UNSIGNED_BYTE, bs.getBuffer() );
    }

    //dtor
    dpapi_opengl1o5_texture::~dpapi_opengl1o5_texture( void )
    {
        this->unlink();
    }

    //generate readlock
    dpshared_readlock *dpapi_opengl1o5_texture::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_opengl1o5_texture_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_opengl1o5_texture::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_opengl1o5_texture_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_opengl1o5_texture::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_opengl1o5_texture_ref( this, k, t_sync );
    }

}










