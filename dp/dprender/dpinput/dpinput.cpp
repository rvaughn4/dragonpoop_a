
/*

*/

#include "dpinput.h"
#include "dpinput_ref.h"
#include "dpinput_readlock.h"
#include "dpinput_writelock.h"

namespace dp
{

    //ctor
    dpinput::dpinput( void ) : dpshared()
    {
        unsigned int i;
        dpinput_event *p;

        for( i = 0; i < dpinput_events_max; i++ )
        {
            p = &this->events[ i ];
            p->h.t = 0;
        }
    }

    //dtor
    dpinput::~dpinput( void )
    {

    }

    //returns next free event or oldest event
    dpinput_event *dpinput::allocEvent( void )
    {
        unsigned int i;
        dpinput_event *p, *r;

        for( r = 0, i = 0; i < dpinput_events_max; i++ )
        {
            p = &this->events[ i ];

            if( !r )
            {
                r = p;
                continue;
            }

            if( p->h.t < r->h.t )
                r = p;
        }

        return r;
    }

    //get newest event time
    uint64_t dpinput::getNewestTime( void )
    {
        unsigned int i;
        dpinput_event *p, *r;

        for( r = 0, i = 0; i < dpinput_events_max; i++ )
        {
            p = &this->events[ i ];

            if( !r )
            {
                r = p;
                continue;
            }

            if( p->h.t > r->h.t )
                r = p;
        }

        if( !r )
            return 0;
        return r->h.t;
    }

    //generate readlock
    dpshared_readlock *dpinput::genReadLock( dpmutex_readlock *ml )
    {
        return new dpinput_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpinput::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpinput_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpinput::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpinput_ref( this, k, t_sync );
    }

    //override to handle sync copy, be sure to call base class first!
    void dpinput::onSync( dpshared_readlock *psync )
    {
        dpinput_event *elist[ dpinput_events_max ];
        uint64_t t;
        unsigned int i, j;
        dpinput_readlock *p;

        this->dpshared::onSync( psync );

        if( !psync->isSyncType( "dpinput" ) )
            return;

        p = (dpinput_readlock *)psync;

        t = this->getNewestTime();
        j = p->getEvents( elist, dpinput_events_max, t );

        for( i = 0; i < j; i++ )
            this->addEvent( elist[ i ] );
        this->update();
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dpinput::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( this->dpshared::isSyncType( ctypename ) )
            return 1;

        return s.compare( "dpinput" ) == 0;
    }

    //override to handle processing
    void dpinput::onRun( dpshared_writelock *wl )
    {
        this->dpshared::onRun( wl );
    }

    //add mouse event
    void dpinput::addMouseEvent( float x, float y, float sx, float sy, bool bIsRight, bool bIsDown )
    {
        dpinput_event e;

        e.mse.h.etype = dpinput_event_type_mouse;
        e.mse.h.t = this->getTicks();
        e.mse.x = x;
        e.mse.y = y;
        e.mse.sx = sx;
        e.mse.sy = sy;
        e.mse.isRight = bIsRight;
        e.mse.isDown = bIsDown;

        this->addEvent( &e );
    }

    //add keypress event
    void dpinput::addKeyPressEvent( bool bIsDown, std::string *sname )
    {
        dpinput_event e;

        e.keyp.h.etype = dpinput_event_type_keypress;
        e.keyp.h.t = this->getTicks();
        e.keyp.bIsDown = bIsDown;
        sname->copy( e.keyp.keyName, dpinput_event_keypress_name_max );

        this->addEvent( &e );
    }

    //add text event
    void dpinput::addTextEvent( std::string *stxt )
    {
        dpinput_event e;

        e.txt.h.etype = dpinput_event_type_text;
        e.txt.h.t = this->getTicks();
        stxt->copy( e.txt.txt, dpinput_event_text_txt_max );

        this->addEvent( &e );
    }

    //add event
    void dpinput::addEvent( dpinput_event *e )
    {
        dpinput_event *ne;

        ne = this->allocEvent();
        if( ne )
            *ne = *e;
    }

    //get events newer than time
    unsigned int dpinput::getEvents( dpinput_event **elist, unsigned int max_sz, uint64_t t )
    {
        unsigned int i, j;
        dpinput_event *p;

        for( j = 0, i = 0; i < dpinput_events_max; i++ )
        {
            p = &this->events[ i ];

            if( p->h.t < t || !p->h.t )
                continue;

            if( j >= max_sz )
                continue;
            elist[ j ] = p;
            j++;
        }

        return j;
    }

}






