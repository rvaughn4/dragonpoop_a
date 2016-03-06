
/*

*/

#ifndef dpapi_opengl1o5_context_h
#define dpapi_opengl1o5_context_h

#include "../../dpapi/dpapi_context/dpapi_context.h"

namespace dp
{

    class dpapi_opengl1o5_context_writelock;

    class dpapi_opengl1o5_context : public dpapi_context
    {

    private:


    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //generate renderpass
        virtual dpapi_renderpass *makeRenderpass( dpapi_opengl1o5_context_writelock *l );

    public:

        //ctor
        dpapi_opengl1o5_context( dpapi_writelock *awl );
        //dtor
        virtual ~dpapi_opengl1o5_context( void );

        friend class dpapi_opengl1o5_context_writelock;
        friend class dpapi_opengl1o5_context_readlock;
    };

}

#endif







