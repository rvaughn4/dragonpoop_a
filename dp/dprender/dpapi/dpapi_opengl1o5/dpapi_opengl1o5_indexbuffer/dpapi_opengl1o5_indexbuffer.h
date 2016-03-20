
/*

*/

#ifndef dpapi_opengl1o5_indexbuffer_h
#define dpapi_opengl1o5_indexbuffer_h

#include "../../dpapi/dpapi_indexbuffer/dpapi_indexbuffer.h"
#include "../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"
#include "../../../dpvertex/dpindexbuffer.h"
#include "../../../../dpcore/dpshared/dpshared_guard.h"

namespace dp
{

    class dpapi_opengl1o5_indexbuffer_writelock;
    class dpapi_opengl1o5_context_writelock;
    class dpapi_opengl1o5_context_ref;

    class dpapi_opengl1o5_indexbuffer : public dpapi_indexbuffer
    {

    private:

        dpshared_guard g;
        opengl1o5_lib_functions *gl;
        unsigned int ibo;
        dpindexbuffer ib;
        dpapi_opengl1o5_context_ref *ctxr;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //return ibo
        unsigned int getIBO( void );
        //return vb
        dpindexbuffer *getIB( void );

    public:

        //ctor
        dpapi_opengl1o5_indexbuffer( dpapi_opengl1o5_context_writelock *ctx, dpindexbuffer *ib, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_indexbuffer( void );

        friend class dpapi_opengl1o5_indexbuffer_writelock;
        friend class dpapi_opengl1o5_indexbuffer_readlock;
    };

}

#endif











