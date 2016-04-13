
/*

*/

#ifndef dpapi_h
#define dpapi_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dpapi_writelock;
    class dpwindow;
    class dpwindow_factory;
    class dpwindow_writelock;
    class dpapi_context;

    class dpapi : public dpshared
    {

    private:

        dpwindow *w;
        dpwindow_factory *wf;
        bool bIsStarted, bIsOpen;
        unsigned int width, height;

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
        //returns true if open
        virtual bool isOpen( void );
        //override to init api
        virtual bool initApi( dpwindow_writelock *wl, dpapi_writelock *al );
        //override to run api
        virtual void runApi( dpapi_writelock *al );
        //override to generate rendering context
        virtual dpapi_context *makeContext( dpapi_writelock *al );
        //override to handle end of frame
        virtual void onFrameEnd( void );
        //override to handle start of frame
        virtual void onFrameStart( void );
        //get dimensions
        virtual void getDimensions( unsigned int **w, unsigned int **h );

    public:

        //ctor
        dpapi( dpwindow_factory *wf );
        //dtor
        virtual ~dpapi( void );

        friend class dpapi_writelock;
        friend class dpapi_readlock;
    };

}

#endif





