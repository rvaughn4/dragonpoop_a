
/*

*/

#ifndef dpapi_texture_h
#define dpapi_texture_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpapi_texture_writelock;
    class dpapi_context_writelock;
    class dpbitmap;

    class dpapi_texture : public dpshared
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
        dpapi_texture( dpapi_context_writelock *ctx, dpbitmap *bm );
        //dtor
        virtual ~dpapi_texture( void );

        friend class dpapi_texture_writelock;
        friend class dpapi_texture_readlock;
    };

}

#endif








