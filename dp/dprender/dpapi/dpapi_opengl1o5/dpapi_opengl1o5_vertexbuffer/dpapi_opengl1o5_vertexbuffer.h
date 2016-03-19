
/*

*/

#ifndef dpapi_opengl1o5_vertexbuffer_h
#define dpapi_opengl1o5_vertexbuffer_h

#include "../../dpapi/dpapi_vertexbuffer/dpapi_vertexbuffer.h"

namespace dp
{

    class dpapi_opengl1o5_vertexbuffer_writelock;
    class dpapi_opengl1o5_context_writelock;

    class dpapi_opengl1o5_vertexbuffer : public dpapi_vertexbuffer
    {

    private:


    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

    public:

        //ctor
        dpapi_opengl1o5_vertexbuffer( dpapi_opengl1o5_context_writelock *ctx, dpvertexbuffer *vb );
        //dtor
        virtual ~dpapi_opengl1o5_vertexbuffer( void );

        friend class dpapi_opengl1o5_vertexbuffer_writelock;
        friend class dpapi_opengl1o5_vertexbuffer_readlock;
    };

}

#endif










