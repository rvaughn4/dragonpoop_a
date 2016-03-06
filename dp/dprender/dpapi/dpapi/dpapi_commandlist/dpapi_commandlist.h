
/*

*/

#ifndef dpapi_commandlist_h
#define dpapi_commandlist_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpapi_context_writelock;

    class dpapi_commandlist : public dpshared
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
        dpapi_commandlist( dpapi_context_writelock *ctxl );
        //dtor
        virtual ~dpapi_commandlist( void );

        friend class dpapi_commandlist_writelock;
        friend class dpapi_commandlist_readlock;
    };

}

#endif







