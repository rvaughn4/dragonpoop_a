
/*

*/

#ifndef dpapi_opengl1o5_context_h
#define dpapi_opengl1o5_context_h

#include "../../dpapi/dpapi_context/dpapi_context.h"
#include "../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"

namespace dp
{

    class dpapi_opengl1o5_context_writelock;

    class dpapi_opengl1o5_context : public dpapi_context
    {

    private:

        opengl1o5_lib_functions *gl;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //generate renderpass
        virtual dpapi_renderpass *makeRenderpass( dpapi_opengl1o5_context_writelock *l );
        //generate primary commandlist
        virtual dpapi_primary_commandlist *makePrimaryCommandList( dpapi_context_writelock *l );
        //generate vertex buffer
        virtual dpapi_vertexbuffer *makeVertexBuffer( dpapi_context_writelock *l, dpvertexbuffer *vb );

    public:

        //ctor
        dpapi_opengl1o5_context( dpapi_writelock *awl, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_context( void );

        friend class dpapi_opengl1o5_context_writelock;
        friend class dpapi_opengl1o5_context_readlock;
    };

}

#endif







