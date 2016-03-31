
/*

*/

#ifndef dpapi_opengl1o5_texture_h
#define dpapi_opengl1o5_texture_h

#include "../../dpapi/dpapi_texture/dpapi_texture.h"
#include "../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"
#include "../../../../dpcore/dpshared/dpshared_guard.h"

namespace dp
{

    class dpapi_opengl1o5_texture_writelock;
    class dpapi_opengl1o5_context_writelock;
    class dpapi_opengl1o5_context_ref;

    class dpapi_opengl1o5_texture : public dpapi_texture
    {

    private:

        opengl1o5_lib_functions *gl;
        unsigned int gltex;
        dpapi_opengl1o5_context_ref *ctx;
        dpshared_guard g;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //return texture gluint
        unsigned int getTex( void );

    public:

        //ctor
        dpapi_opengl1o5_texture( dpapi_opengl1o5_context_writelock *ctx, dpbitmap *bm, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_texture( void );

        friend class dpapi_opengl1o5_texture_writelock;
        friend class dpapi_opengl1o5_texture_readlock;
    };

}

#endif









