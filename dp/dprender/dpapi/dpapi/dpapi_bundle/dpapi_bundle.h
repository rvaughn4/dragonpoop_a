
/*

*/

#ifndef dpapi_bundle_h
#define dpapi_bundle_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpapi_bundle_writelock;
    class dpapi_context_writelock;
    class dpapi_vertexbuffer;
    class dpapi_indexbuffer;
    class dpapi_material;
    class dpapi_texture;

    class dpapi_bundle : public dpshared
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
        dpapi_bundle( dpapi_context_writelock *ctx, dpapi_vertexbuffer *vb, dpapi_indexbuffer *ib, dpapi_material *m, dpapi_texture *t0, dpapi_texture *t1 );
        //ctor
        dpapi_bundle( dpapi_context_writelock *ctx, dpapi_bundle *bdle );
        //dtor
        virtual ~dpapi_bundle( void );

        friend class dpapi_bundle_writelock;
        friend class dpapi_bundle_readlock;
    };

}

#endif







