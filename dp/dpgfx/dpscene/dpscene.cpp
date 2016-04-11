/*

*/

#include "dpscene.h"
#include "dpscene_ref.h"
#include "dpscene_readlock.h"
#include "dpscene_writelock.h"
#include "../dpgui/dpgui.h"
#include "../dpgui/dpgui_writelock.h"
#include <string>

namespace dp
{

    //ctor
    dpscene::dpscene( void ) : dptask( "scene", 500 )
    {
        this->root_gui = 0;
    }

    //dtor
    dpscene::~dpscene( void )
    {
        this->waitForStop();
        this->unlink();
        if( this->root_gui )
            delete this->root_gui;
    }

    //generate readlock
    dpshared_readlock *dpscene::genReadLock( dpmutex_readlock *ml )
    {
        return new dpscene_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpscene::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpscene_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpscene::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpscene_ref( this, k, t_sync );
    }

    //override to do task execution
    bool dpscene::onTaskRun( dptask_writelock *tl )
    {
        return this->onSceneRun( (dpscene_writelock *)tl );
    }

    //override to do task startup
    bool dpscene::onTaskStart( dptask_writelock *tl )
    {
        this->root_gui = new dpgui( 20, 20, 300, 300, "hello!" );
        this->addDynamicTask( this->root_gui );

        return this->onSceneStart( (dpscene_writelock *)tl );
    }

    //override to do task shutdown
    bool dpscene::onTaskStop( dptask_writelock *tl )
    {
        dpgui_writelock *l;
        dpshared_guard g;

        if( !this->onSceneStop( (dpscene_writelock *)tl ) )
            return 0;

        l = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->root_gui, 1000 );
        if( l )
            l->stop();

        return 1;
    }

    //override to handle sync copy, be sure to call base class first!
    void dpscene::onSync( dpshared_readlock *psync )
    {
        this->dptask::onSync( psync );
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dpscene::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( s.compare( "dpscene" ) == 0 )
            return 1;

        return this->dptask::isSyncType( ctypename );
    }

    //override to handle scene start
    bool dpscene::onSceneStart( dpscene_writelock *sl )
    {
        return 1;
    }

    //override to handle scene stop
    bool dpscene::onSceneStop( dpscene_writelock *sl )
    {
        return 1;
    }

    //override to handle scene run
    bool dpscene::onSceneRun( dpscene_writelock *sl )
    {
        return 1;
    }

    //return root gui
    dpgui *dpscene::getGui( void )
    {
        return this->root_gui;
    }

};

