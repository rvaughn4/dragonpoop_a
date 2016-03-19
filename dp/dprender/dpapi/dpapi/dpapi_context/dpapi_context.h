
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
    class dpapi_writelock;
    class dpapi_renderpass;
    class dpapi_commandlist;
    class dpapi_primary_commandlist;
    class dpapi_vertexbuffer;
    class dpvertexbuffer;

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
        //generate renderpass
        virtual dpapi_renderpass *makeRenderpass( dpapi_context_writelock *l );
        //generate primary commandlist
        virtual dpapi_primary_commandlist *makePrimaryCommandList( dpapi_context_writelock *l );
        //generate secondary commandlist
        virtual dpapi_commandlist *makeCommandList( dpapi_context_writelock *l );
        //generate vertex buffer
        virtual dpapi_vertexbuffer *makeVertexBuffer( dpapi_context_writelock *l, dpvertexbuffer *vb );

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






