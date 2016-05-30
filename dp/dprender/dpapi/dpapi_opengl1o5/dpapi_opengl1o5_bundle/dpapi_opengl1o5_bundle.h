
/*

*/

#ifndef dpapi_opengl1o5_bundle_h
#define dpapi_opengl1o5_bundle_h

#include "../../dpapi/dpapi_bundle/dpapi_bundle.h"
#include "../../../../dpgfx/dpvertex/dpvertexbuffer.h"
#include "../../../../dpgfx/dpvertex/dpindexbuffer.h"
#include "../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"
#include "../../../../dpgfx/dpmatrix/dpmatrix.h"

namespace dp
{

    class dpapi_opengl1o5_vertexbuffer;
    class dpapi_opengl1o5_indexbuffer;
    class dpapi_opengl1o5_material;
    class dpapi_opengl1o5_texture;
    class dpapi_context_writelock;
    struct opengl1o5_lib_functions;
    class dpapi_opengl1o5_context_writelock;

    class dpapi_opengl1o5_bundle : public dpapi_bundle
    {

    private:

        dpvertexbuffer vb;
        dpindexbuffer ib;
        opengl1o5_lib_functions *gl;
        unsigned int vbo, ibo, cnt, t1, t0;
        dpmatrix m;
        float opacity;

    protected:

        //compile bundle
        virtual bool compile( dpapi_context_writelock *ctx, dpapi_bundle_writelock *l );
        //execute bundle
        virtual bool execute( dpapi_context_writelock *ctx, dpapi_bundle_writelock *l );

    public:

        //ctor
        dpapi_opengl1o5_bundle( dpapi_opengl1o5_context_writelock *ctx, dpmatrix *mx, dpapi_opengl1o5_vertexbuffer *vb, dpapi_opengl1o5_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1, opengl1o5_lib_functions *gl );
        //ctor
        dpapi_opengl1o5_bundle( dpapi_opengl1o5_context_writelock *ctx, dpmatrix *mx, dpapi_opengl1o5_bundle *bdle, float opacity );
        //dtor
        virtual ~dpapi_opengl1o5_bundle( void );

    };

}

#endif








