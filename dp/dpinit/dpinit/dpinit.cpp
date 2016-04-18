
/*

*/

#include "dpinit.h"
#include "../../dpcore/dptaskmgr/dptaskmgr.h"
#include "../../dpcore/dptaskmgr/dptaskmgr_writelock.h"
#include "../../dpgfx/dpgfx/dpgfx.h"
#include "../../dpgfx/dpgfx/dpgfx_writelock.h"
#include "../../dpgfx/dpgfx/dpgfx_readlock.h"
#include "../../dpgfx/dpscene/dpscene.h"
#include "../../dpgfx/dpscene/dpscene_writelock.h"
#include "../../dpcore/dpshared/dpshared_guard.h"
#include "../dploader_scene/dploader_scene/dploader_scene.h"
#include <thread>

namespace dp
{

    //ctor
    dpinit::dpinit( void )
    {
        this->tskmgr = 0;
        this->gfx = 0;
    }

    //dtor
    dpinit::~dpinit( void )
    {
        this->stop();
    }

    //start dp
    bool dpinit::start( void )
    {
        dpshared_guard g;
        dptaskmgr_writelock *l;
        dpscene *ns;
        dpgfx_writelock *gl;

        this->stop();

        this->tskmgr = new dp::dptaskmgr( 4 );
        if( !this->tskmgr )
            return 0;

        this->gfx = new dp::dpgfx();
        if( !this->gfx )
            return 0;

        l = (dptaskmgr_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->tskmgr, 2000 );
        if( !l )
            return 0;

        l->addStaticTask( this->gfx, 1 );
        g.release( l );
        std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

        gl = (dpgfx_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->gfx, 2000 );
        if( !gl )
            return 0;

        ns = new dploader_scene();
        if( !gl->addScene( &ns ) )
            return 0;
        g.release( gl );

        std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );
        return 1;
    }

    //stop dp
    void dpinit::stop( void )
    {
        if( this->gfx )
            delete this->gfx;
        this->gfx = 0;
        if( this->tskmgr )
            delete this->tskmgr;
        this->tskmgr = 0;
    }

    //set first scene
    void dpinit::setFirstScene( void )
    {

    }

    //block until engine dies
    void dpinit::blockUntilDead( void )
    {
        while( this->isAlive() )
            std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    }

    //returns true if engine is running
    bool dpinit::isAlive( void )
    {
        dpshared_guard g;
        dpgfx_readlock *l;

        if( !this->gfx )
            return 0;

        l = (dpgfx_readlock *)dpshared_guard_tryReadLock_timeout( g, this->gfx, 2000 );
        if( !l )
            return 0;

        return l->isRun();
    }

};


