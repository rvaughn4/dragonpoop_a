
/*

*/

#include "dpapi_opengl1o5_indexbuffer.h"
#include "dpapi_opengl1o5_indexbuffer_ref.h"
#include "dpapi_opengl1o5_indexbuffer_readlock.h"
#include "dpapi_opengl1o5_indexbuffer_writelock.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_writelock.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_ref.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_indexbuffer::dpapi_opengl1o5_indexbuffer( dpapi_opengl1o5_context_writelock *ctx, dpindexbuffer *ib, opengl1o5_lib_functions *gl ) : dpapi_indexbuffer( ctx, ib )
    {
        this->gl = gl;
        this->ibo = 0;
        this->ctxr = (dpapi_opengl1o5_context_ref *)this->g.getRef( ctx );

        ctx->makeActive();

        if( this->gl->bUseVB )
        {
            this->gl->glGenBuffers( 1, &this->ibo );
            if( this->ibo )
            {
                this->gl->glBindBuffer( opengl1o5_lib_ELEMENT_ARRAY_BUFFER, this->ibo );
                this->gl->glBufferData( opengl1o5_lib_ELEMENT_ARRAY_BUFFER, ib->getSize(), 0, opengl1o5_lib_STATIC_DRAW );
            }
        }

        if( !this->ibo )
            this->ib.copy( ib );
    }

    //dtor
    dpapi_opengl1o5_indexbuffer::~dpapi_opengl1o5_indexbuffer( void )
    {
        dpapi_opengl1o5_context_writelock *l;

        if( this->ibo )
        {
            l = (dpapi_opengl1o5_context_writelock *)dpshared_guard_tryWriteLock_timeout( this->g, this->ctxr, 2000 );
            if( l )
            {
                l->makeActive();
                this->gl->glDeleteBuffers( 1, &this->ibo );
                this->g.release( l );
            }
        }

        this->g.release( this->ctxr );
    }

    //generate readlock
    dpshared_readlock *dpapi_opengl1o5_indexbuffer::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_opengl1o5_indexbuffer_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_opengl1o5_indexbuffer::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_opengl1o5_indexbuffer_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_opengl1o5_indexbuffer::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_opengl1o5_indexbuffer_ref( this, k, t_sync );
    }

    //return ibo
    unsigned int dpapi_opengl1o5_indexbuffer::getIBO( void )
    {
        return this->ibo;
    }

    //return vb
    dpindexbuffer *dpapi_opengl1o5_indexbuffer::getIB( void )
    {
        return &this->ib;
    }

}












