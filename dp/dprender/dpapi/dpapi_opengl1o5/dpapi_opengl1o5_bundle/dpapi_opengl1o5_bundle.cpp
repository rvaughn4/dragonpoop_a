
/*

*/

#include "dpapi_opengl1o5_bundle.h"
#include "../dpapi_opengl1o5_context/dpapi_opengl1o5_context_writelock.h"
#include "../dpapi_opengl1o5_vertexbuffer/dpapi_opengl1o5_vertexbuffer.h"
#include "../dpapi_opengl1o5_vertexbuffer/dpapi_opengl1o5_vertexbuffer_writelock.h"
#include "../../../../dpcore/dpshared/dpshared_guard.h"

namespace dp
{

    //ctor
    dpapi_opengl1o5_bundle::dpapi_opengl1o5_bundle( dpapi_opengl1o5_context_writelock *ctx, dpapi_opengl1o5_vertexbuffer *vb, dpapi_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1, opengl1o5_lib_functions *gl ) : dpapi_bundle( ctx, vb, ib, m, t0, t1 )
    {
        dpshared_guard g;
        dpapi_opengl1o5_vertexbuffer_writelock *vbl;

        this->gl = gl;

        vbl = (dpapi_opengl1o5_vertexbuffer_writelock *)dpshared_guard_tryWriteLock_timeout( g, vb, 1000 );
        if( vbl )
            this->vb.copy( vbl->getVB() );

    }

    //ctor
    dpapi_opengl1o5_bundle::dpapi_opengl1o5_bundle( dpapi_opengl1o5_context_writelock *ctx, dpapi_opengl1o5_bundle *bdle ) : dpapi_bundle( ctx, bdle )
    {
        this->gl = bdle->gl;
        this->vb.copy( &bdle->vb );
    }

    //dtor
    dpapi_opengl1o5_bundle::~dpapi_opengl1o5_bundle( void )
    {

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

        c = (dpapi_opengl1o5_context_writelock *)ctx;
        v = 0;

        c->makeActive();

        this->gl->glNormalPointer( opengl1o5_lib_FLOAT, sizeof( dpvertex ), &v->norm.x );
        this->gl->glTexCoordPointer( 2, opengl1o5_lib_FLOAT, sizeof( dpvertex ), &v->texcoord[ 0 ].s );
        this->gl->glVertexPointer( 3, opengl1o5_lib_FLOAT, sizeof( dpvertex ), &v->vert.x );

        this->gl->glDrawElements( opengl1o5_lib_TRIANGLES, 0, opengl1o5_lib_UNSIGNED_SHORT, 0 );

        return 1;
    }

}









