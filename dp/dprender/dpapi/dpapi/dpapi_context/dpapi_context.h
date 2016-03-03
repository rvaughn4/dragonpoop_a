
/*

*/

#ifndef dpapi_context_h
#define dpapi_context_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dpapi_context_writelock;
    class dpapi;
    class dpapi_writelock;

    class dpapi_context : public dpshared
    {

    private:


    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to handle sync copy, be sure to call base class first!
        virtual void onSync( dpshared_readlock *psync );
        //override to test type for safe syncing, be sure to call base class first!
        virtual bool isSyncType( const char *ctypename );
        //override to handle processing
        virtual void onRun( dpshared_writelock *wl );

    public:

        //ctor
        dpapi_context( dpapi_writelock *awl );
        //dtor
        virtual ~dpapi_context( void );

        friend class dpapi_context_writelock;
        friend class dpapi_context_readlock;
    };

}

#endif






