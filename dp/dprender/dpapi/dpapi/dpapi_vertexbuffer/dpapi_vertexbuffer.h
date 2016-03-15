
/*

*/

#ifndef dpapi_vertexbuffer_h
#define dpapi_vertexbuffer_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpapi_vertexbuffer_writelock;
    class dpapi_context_writelock;

    class dpapi_vertexbuffer : public dpshared
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
        dpapi_vertexbuffer( dpapi_context_writelock *ctx );
        //dtor
        virtual ~dpapi_vertexbuffer( void );

        friend class dpapi_vertexbuffer_writelock;
        friend class dpapi_vertexbuffer_readlock;
    };

}

#endif









