
/*

*/

#include "dpapi_opengl1o5_vertexbuffer.h"
#include "dpapi_opengl1o5_vertexbuffer_ref.h"
#include "dpapi_opengl1o5_vertexbuffer_readlock.h"
#include "dpapi_opengl1o5_vertexbuffer_writelock.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_writelock.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_ref.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_vertexbuffer::dpapi_opengl1o5_vertexbuffer( dpapi_opengl1o5_context_writelock *ctx, dpvertexbuffer *vb, opengl1o5_lib_functions *gl ) : dpapi_vertexbuffer( ctx, vb )
    {
        this->gl = gl;
        this->vbo = 0;
        this->ctxr = (dpapi_opengl1o5_context_ref *)this->g.getRef( ctx );

        ctx->makeActive();

        if( this->gl->bUseVB )
        {
            this->gl->glGenBuffers( 1, &this->vbo );
            if( this->vbo )
            {
                this->gl->glBindBuffer( opengl1o5_lib_ARRAY_BUFFER, this->vbo );
                this->gl->glBufferData( opengl1o5_lib_ARRAY_BUFFER, vb->getSize(), 0, opengl1o5_lib_STATIC_DRAW );
            }
        }

        if( !this->vbo )
            this->vb.copy( vb );
    }

    //dtor
    dpapi_opengl1o5_vertexbuffer::~dpapi_opengl1o5_vertexbuffer( void )
    {
        dpapi_opengl1o5_context_writelock *l;

        this->unlink();

        if( this->vbo )
        {
            l = (dpapi_opengl1o5_context_writelock *)dpshared_guard_tryWriteLock_timeout( this->g, this->ctxr, 2000 );
            if( l )
            {
                l->makeActive();
                this->gl->glDeleteBuffers( 1, &this->vbo );
                this->g.release( l );
            }
        }

        this->g.release( this->ctxr );
    }

    //generate readlock
    dpshared_readlock *dpapi_opengl1o5_vertexbuffer::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_opengl1o5_vertexbuffer_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_opengl1o5_vertexbuffer::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_opengl1o5_vertexbuffer_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_opengl1o5_vertexbuffer::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_opengl1o5_vertexbuffer_ref( this, k, t_sync );
    }

    //return vbo
    unsigned int dpapi_opengl1o5_vertexbuffer::getVBO( void )
    {
        return this->vbo;
    }

    //return vb
    dpvertexbuffer *dpapi_opengl1o5_vertexbuffer::getVB( void )
    {
        return &this->vb;
    }

}











