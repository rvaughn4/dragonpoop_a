
/*

*/

#ifndef dpapi_opengl1o5_h
#define dpapi_opengl1o5_h

#include "../../dpapi/dpapi/dpapi.h"

namespace dp
{

    class dpapi_opengl1o5_writelock;

    class dpapi_opengl1o5 : public dpapi
    {

    private:

        dpwindow *w;
        dpwindow_factory *wf;
        bool bIsStarted, bIsOpen;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to init api
        virtual bool initApi( dpwindow_writelock *wl, dpapi_writelock *al );
        //override to run api
        virtual void runApi( dpapi_writelock *al );
        //override to generate rendering context
        virtual dpapi_context *makeContext( dpapi_writelock *al );

    public:

        //ctor
        dpapi_opengl1o5( dpwindow_factory *wf );
        //dtor
        virtual ~dpapi_opengl1o5( void );

        friend class dpapi_opengl1o5_writelock;
        friend class dpapi_opengl1o5_readlock;
    };

}

#endif






