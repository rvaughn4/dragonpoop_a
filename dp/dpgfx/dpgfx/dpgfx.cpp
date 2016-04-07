
/*
gpgfx manages models and gui elements and scenes
*/

#include "dpgfx.h"
#include "dpgfx_ref.h"
#include "dpgfx_readlock.h"
#include "dpgfx_writelock.h"
#include "../dpscene/dpscene.h"
#include "../dpscene/dpscene_writelock.h"

namespace dp
{

   //ctor
    dpgfx::dpgfx( void ) : dptask( "Graphics", 100 )
    {
        this->zeroScenes();
    }

    //dtor
    dpgfx::~dpgfx( void )
    {
        this->unlink();
        this->waitForStop();
        this->deleteScenes();
    }

    //generate readlock
    dpshared_readlock *dpgfx::genReadLock( dpmutex_readlock *ml )
    {
        return new dpgfx_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpgfx::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpgfx_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpgfx::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpgfx_ref( this, k, t_sync );
    }

    //override to do task execution
    bool dpgfx::onTaskRun( dptask_writelock *tl )
    {
        return 1;
    }

    //override to do task startup
    bool dpgfx::onTaskStart( dptask_writelock *tl )
    {
        return 1;
    }

    //override to do task shutdown
    bool dpgfx::onTaskStop( dptask_writelock *tl )
    {
        this->stopScenes();
        return 1;
    }

    //zero scenes
    void dpgfx::zeroScenes( void )
    {
        unsigned int i;

        for( i = 0; i < dpgfx_max_scenes; i++ )
            this->scenes[ i ] = 0;
    }

    //delete scenes
    void dpgfx::deleteScenes( void )
    {
        unsigned int i;
        dpscene *p;

        for( i = 0; i < dpgfx_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;
            delete p;
        }

        this->zeroScenes();
    }

    //stop scenes
    void dpgfx::stopScenes( void )
    {
        unsigned int i;
        dpscene *p;
        dpscene_writelock *pl;
        dpshared_guard g;

        for( i = 0; i < dpgfx_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;

            pl = (dpscene_writelock *)dpshared_guard_tryWriteLock_timeout( g, p, 100 );
            if( !pl )
                continue;
            pl->stop();

            if( pl->isRun() )
            {
                g.release( pl );
                continue;
            }

            g.release( pl );
            delete p;
            this->scenes[ i ] = 0;
        }
    }

    //add scene
    bool dpgfx::addScene( dpscene **s )
    {
        unsigned int i;
        dpscene *p;

        if( !s || !*s )
            return 0;

        for( i = 0; i < dpgfx_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( p )
                continue;

            p = *s;
            this->scenes[ i ] = p;
            this->addDynamicTask( p );
            return 1;
        }

        delete *s;
        return 0;
    }

}






