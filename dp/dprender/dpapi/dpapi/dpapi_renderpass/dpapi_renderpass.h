
/*

*/

#ifndef dpapi_renderpass_h
#define dpapi_renderpass_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dpapi_renderpass_writelock;
    class dpapi_context_writelock;

    class dpapi_renderpass : public dpshared
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
        dpapi_renderpass( dpapi_context_writelock *awl );
        //dtor
        virtual ~dpapi_renderpass( void );

        friend class dpapi_renderpass_writelock;
        friend class dpapi_renderpass_readlock;
    };

}

#endif







