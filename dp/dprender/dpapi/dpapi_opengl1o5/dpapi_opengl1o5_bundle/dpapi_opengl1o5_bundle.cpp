
/*

*/

#include "dpapi_opengl1o5_bundle.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_writelock.h"
#include "../dpapi_opengl1o5_vertexbuffer/dpapi_opengl1o5_vertexbuffer.h"
#include "../dpapi_opengl1o5_vertexbuffer/dpapi_opengl1o5_vertexbuffer_writelock.h"
#include "../dpapi_opengl1o5_indexbuffer/dpapi_opengl1o5_indexbuffer.h"
#include "../dpapi_opengl1o5_indexbuffer/dpapi_opengl1o5_indexbuffer_writelock.h"
#include "../dpapi_opengl1o5_texture/dpapi_opengl1o5_texture.h"
#include "../dpapi_opengl1o5_texture/dpapi_opengl1o5_texture_writelock.h"
#include "../../../../dpcore/dpshared/dpshared_guard.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_bundle::dpapi_opengl1o5_bundle( dpapi_opengl1o5_context_writelock *ctx, dpmatrix *mx, dpapi_opengl1o5_vertexbuffer *vb, dpapi_opengl1o5_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1, opengl1o5_lib_functions *gl ) : dpapi_bundle( ctx, mx, vb, ib, m, t0, t1 )
    {
        dpshared_guard g;
        dpapi_opengl1o5_vertexbuffer_writelock *vbl;
        dpapi_opengl1o5_indexbuffer_writelock *ibl;
        dpapi_opengl1o5_texture_writelock *tl;

        this->gl = gl;
        this->cnt = 0;
        this->vbo = 0;
        this->ibo = 0;
        this->t0 = 0;
        this->t1 = 0;
        if( mx )
            this->m.copy( mx );

        vbl = (dpapi_opengl1o5_vertexbuffer_writelock *)dpshared_guard_tryWriteLock_timeout( g, vb, 1000 );
        if( vbl )
        {
            this->vbo = vbl->getVBO();
            this->vb.copy( vbl->getVB() );
        }
        ibl = (dpapi_opengl1o5_indexbuffer_writelock *)dpshared_guard_tryWriteLock_timeout( g, ib, 1000 );
        if( ibl )
        {
            this->ibo = ibl->getIBO();
            this->cnt = ibl->getCount();
            this->ib.copy( ibl->getIB() );
        }

        tl = (dpapi_opengl1o5_texture_writelock *)dpshared_guard_tryWriteLock_timeout( g, t0, 1000 );
        if( tl )
            this->t0 = tl->getTex();

        tl = (dpapi_opengl1o5_texture_writelock *)dpshared_guard_tryWriteLock_timeout( g, t1, 1000 );
        if( tl )
            this->t1 = tl->getTex();
    }

    //ctor
    dpapi_opengl1o5_bundle::dpapi_opengl1o5_bundle( dpapi_opengl1o5_context_writelock *ctx, dpmatrix *mx, dpapi_opengl1o5_bundle *bdle ) : dpapi_bundle( ctx, mx, bdle )
    {
        this->gl = bdle->gl;
        this->vb.copy( &bdle->vb );
        this->ib.copy( &bdle->ib );
        this->vbo = bdle->vbo;
        this->ibo = bdle->ibo;
        this->cnt = bdle->cnt;
        this->t0 = bdle->t0;
        this->t1 = bdle->t1;
        if( mx )
            this->m.copy( mx );
        else
            this->m.copy( &bdle->m );
    }

    //dtor
    dpapi_opengl1o5_bundle::~dpapi_opengl1o5_bundle( void )
    {
        this->unlink();
    }

    //compile bundle
    bool dpapi_opengl1o5_bundle::compile( dpapi_context_writelock *ctx, dpapi_bundle_writelock *l )
    {
        return 1;
    }

    //execute bundle
    bool dpapi_opengl1o5_bundle::execute( dpapi_context_writelock *ctx, dpapi_bundle_writelock *l )
    {
        dpapi_opengl1o5_context_writelock *c;
        dpvertex *v;
        dpindex *i;

        c = (dpapi_opengl1o5_context_writelock *)ctx;
        v = (dpvertex *)this->vb.getBuffer();
        i = (dpindex *)this->ib.getBuffer();

        c->makeActive();

        this->gl->glPushMatrix();
        this->gl->glMultMatrixf( this->m.getRaw4by4() );

        this->gl->glEnableClientState( opengl1o5_lib_NORMAL_ARRAY );
        this->gl->glEnableClientState( opengl1o5_lib_TEXTURE_COORD_ARRAY );
        this->gl->glEnableClientState( opengl1o5_lib_VERTEX_ARRAY );
        this->gl->glEnable( opengl1o5_lib_TEXTURE_2D );

        this->gl->glBindTexture( opengl1o5_lib_TEXTURE_2D, this->t0 );

        if( this->gl->bUseVB )
        {
            if( this->vbo )
            {
                this->gl->glBindBuffer( opengl1o5_lib_ARRAY_BUFFER, this->vbo );
                v = 0;
            }
            else
                this->gl->glBindBuffer( opengl1o5_lib_ARRAY_BUFFER, 0 );

            if( this->ibo )
            {
                this->gl->glBindBuffer( opengl1o5_lib_ELEMENT_ARRAY_BUFFER, this->ibo );
                i = 0;
            }
            else
                this->gl->glBindBuffer( opengl1o5_lib_ELEMENT_ARRAY_BUFFER, 0 );
        }

        this->gl->glNormalPointer( opengl1o5_lib_FLOAT, sizeof( dpvertex ), &v->norm.x );
        this->gl->glTexCoordPointer( 2, opengl1o5_lib_FLOAT, sizeof( dpvertex ), &v->texcoord[ 0 ].s );
        this->gl->glVertexPointer( 3, opengl1o5_lib_FLOAT, sizeof( dpvertex ), &v->vert.x );

        this->gl->glDrawElements( opengl1o5_lib_TRIANGLES, this->cnt, opengl1o5_lib_UNSIGNED_SHORT, i );

        if( this->gl->bUseVB )
        {
            this->gl->glBindBuffer( opengl1o5_lib_ARRAY_BUFFER, 0 );
            this->gl->glBindBuffer( opengl1o5_lib_ELEMENT_ARRAY_BUFFER, 0 );
        }

        this->gl->glPopMatrix();

        return 1;
    }

}









