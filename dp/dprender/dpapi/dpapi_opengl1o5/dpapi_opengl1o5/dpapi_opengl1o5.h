
/*

*/

#ifndef dpapi_opengl1o5_h
#define dpapi_opengl1o5_h

#include "../../dpapi/dpapi/dpapi.h"
#include "dpapi_opengl1o5_functions.h"
#include <string>

namespace dp
{

    class dpapi_opengl1o5_writelock;

    class dpapi_opengl1o5 : public dpapi
    {

    private:

        opengl1o5_lib_functions gl;
        std::string sver, sext;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to init api
        virtual bool initApi( dpwindow_writelock *wl, dpapi_writelock *al );
        //override to generate rendering context
        virtual dpapi_context *makeContext( dpapi_writelock *al );
        //override to load opengl library
        virtual bool loadGL( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al );
        //override to handle loading of function pointers
        virtual void *loadFunction( dpwindow_writelock *wl, dpapi_opengl1o5_writelock *al, const char *cname );
        //override to provide pointer to gl function pointers
        virtual opengl1o5_lib_functions *getGL( void );
        //override to handle end of frame
        virtual void onFrameEnd( void );
        //override to handle start of frame
        virtual void onFrameStart( void );


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






