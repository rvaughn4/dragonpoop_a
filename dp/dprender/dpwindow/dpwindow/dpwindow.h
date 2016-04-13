
/*

*/

#ifndef dpwindow_h
#define dpwindow_h

#include "../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpmutex_readlock;
    class dpmutex_writelock;
    class dpwindow_writelock;

    class dpwindow : public dpshared
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
        //returns true if open
        virtual bool isOpen( void );
        //return width
        virtual unsigned int getWidth( void );
        //return height
        virtual unsigned int getHeight( void );

    public:

        //ctor
        dpwindow( void );
        //dtor
        virtual ~dpwindow( void );

        friend class dpwindow_writelock;
        friend class dpwindow_readlock;
    };

}

#endif




