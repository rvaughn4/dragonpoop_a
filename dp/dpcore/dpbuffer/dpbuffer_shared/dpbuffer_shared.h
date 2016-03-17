
/*
*/

#ifndef dpbuffer_shared_h
#define dpbuffer_shared_h

#include "../../dpshared/dpshared.h"
#include "../dpbuffer_wrapper/dpbuffer_wrapper.h"

namespace dp
{

    class dpbuffer_shared : public dpbuffer_wrapper, public dpshared
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
        dpbuffer_shared( dpbuffer *b );
        //dtor
        virtual ~dpbuffer_shared( void );

        friend class dpbuffer_shared_writelock;
        friend class dpbuffer_shared_readlock;
        friend class dpbuffer_shared_ref;
    };

}

#endif


