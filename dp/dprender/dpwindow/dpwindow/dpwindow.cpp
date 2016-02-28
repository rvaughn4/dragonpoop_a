
/*

*/

#include "dpwindow.h"
#include "dpwindow_ref.h"
#include "dpwindow_readlock.h"
#include "dpwindow_writelock.h"

#include <string>

namespace dp
{

    //ctor
    dpwindow::dpwindow( void ) : dpshared()
    {

    }

    //dtor
    dpwindow::~dpwindow( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpwindow::genReadLock( dpmutex_readlock *ml )
    {
        return new dpwindow_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpwindow::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpwindow_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpwindow::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpwindow_ref( this, k, t_sync );
    }

    //override to handle sync copy, be sure to call base class first!
    void dpwindow::onSync( dpshared_readlock *psync )
    {
        this->dpshared::onSync( psync );
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dpwindow::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( this->dpshared::isSyncType( ctypename ) )
            return 1;

        return s.compare( "dpwindow" ) == 0;
    }

    //override to handle processing
    void dpwindow::onRun( dpshared_writelock *wl )
    {

    }

}





