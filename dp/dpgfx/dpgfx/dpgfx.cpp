
/*
gpgfx manages models and gui elements and scenes
*/

#include "dpgfx.h"
#include "dpgfx_ref.h"
#include "dpgfx_readlock.h"
#include "dpgfx_writelock.h"
#include "../dpscene/dpscene.h"
#include "../dpscene/dpscene_writelock.h"
#include "../dpscene/dpscene_readlock.h"
#include "../../dprender/dprender/dprender/dprender.h"
#include "../../dprender/dprender/dprender/dprender_writelock.h"
#include "../../dprender/dprender/dprender/dprender_readlock.h"

#include "../../dprender/dpapi/dpapi_x11_opengl1o5/dpapi_x11_opengl1o5/dpapi_x11_opengl1o5_factory.h"

namespace dp
{

   //ctor
    dpgfx::dpgfx( void ) : dptask( "Graphics", 100 )
    {
        this->zeroScenes();
        this->renderer = 0;
        this->bd = 0;
    }

    //dtor
    dpgfx::~dpgfx( void )
    {
        if( this->renderer )
            delete this->renderer;
        this->waitForStop();
        this->unlink();
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
        dprender_readlock *rl;
        dpshared_guard g;

        if( !this->renderer )
            this->initAnyRenderer();

        rl = (dprender_readlock *)dpshared_guard_tryReadLock_timeout( g, this->renderer, 10 );
        if( rl )
        {
            if( !rl->isRun() )
            {
                if( this->bd )
                    this->stop();
            }
            else
                this->bd = 1;
        }

        this->deleteOldScenes();

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
        dprender_writelock *l;
        dpshared_guard g;

        if( this->renderer )
        {
            l = (dprender_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->renderer, 1000 );
            if( l )
                l->stop();
            g.release( l );
        }

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

    //delete old scenes, stops task is all scenes are closed out
    void dpgfx::deleteOldScenes( void )
    {
        unsigned int i, sc, ac;
        dpscene *p;
        dpscene_readlock *l;
        dpshared_guard g;
        bool r;

        for( sc = ac = i = 0; i < dpgfx_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;

            l = (dpscene_readlock *)dpshared_guard_tryReadLock_timeout( g, p, 10 );
            if( !l )
                continue;

            r = l->isRun();
            g.release( l );

            sc++;
            if( r )
                ac++;
            else
            {
                delete p;
                this->scenes[ i ] = 0;
            }
        }

        if( ac == 0 && sc > 0 )
            this->stop();
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
            *s = 0;
            return 1;
        }

        *s = 0;
        delete *s;
        return 0;
    }

    //load a renderer
    void dpgfx::initAnyRenderer( void )
    {
        if( this->renderer )
            delete this->renderer;
        this->renderer = new dprender( this, new dpapi_x11_opengl1o5_factory( 640, 480, "render" ) );

        if( this->renderer )
            this->addStaticTask( this->renderer, 1 );
    }

    //get all scenes
    unsigned int dpgfx::getScenes( dpscene **lst, unsigned int max_sz )
    {
        unsigned int i, j;
        dpscene *p;

        for( j = i = 0; i < dpgfx_max_scenes; i++ )
        {
            p = this->scenes[ i ];
            if( !p )
                continue;

            if( j >= max_sz )
                continue;

            lst[ j ] = p;
            j++;
        }
        for( i = j; i < max_sz; i++ )
            lst[ i ] = 0;

        return j;
    }

}






