
/*

*/

#ifndef dpapi_material_h
#define dpapi_material_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpapi_material_writelock;
    class dpapi_context_writelock;

    class dpapi_material : public dpshared
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
        dpapi_material( dpapi_context_writelock *ctx );
        //dtor
        virtual ~dpapi_material( void );

        friend class dpapi_material_writelock;
        friend class dpapi_material_readlock;
    };

}

#endif








