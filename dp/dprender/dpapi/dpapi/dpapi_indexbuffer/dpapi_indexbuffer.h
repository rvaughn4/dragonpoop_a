
/*

*/

#ifndef dpapi_indexbuffer_h
#define dpapi_indexbuffer_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpapi_indexbuffer_writelock;
    class dpapi_context_writelock;
    class dpindexbuffer;

    class dpapi_indexbuffer : public dpshared
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
        dpapi_indexbuffer( dpapi_context_writelock *ctx, dpindexbuffer *ib );
        //dtor
        virtual ~dpapi_indexbuffer( void );

        friend class dpapi_indexbuffer_writelock;
        friend class dpapi_indexbuffer_readlock;
    };

}

#endif








