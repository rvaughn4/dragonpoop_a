/*
represents the lifecycle of a writelock on a dpinput
this object is returned from a dpinput when writelocked
deleting this object releases the writelock on the dpinput
*/

#include "dpinput_writelock.h"

namespace dp
{

    //ctor
    dpinput_writelock::dpinput_writelock( dpinput *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpinput_writelock::~dpinput_writelock( void )
    {

    }

    //get events newer than time
    unsigned int dpinput_writelock::getEvents( dpinput_event **elist, unsigned int max_sz, uint64_t t )
    {
        return this->p->getEvents( elist, max_sz, t );
    }

    //add mouse event
    void dpinput_writelock::addMouseEvent( float x, float y, float sx, float sy, bool bIsRight, bool bIsDown )
    {
        this->p->addMouseEvent( x, y, sx, sy, bIsRight, bIsDown );
    }

    //add keypress event
    void dpinput_writelock::addKeyPressEvent( bool bIsDown, std::string *sname )
    {
        this->p->addKeyPressEvent( bIsDown, sname );
    }

    //add text event
    void dpinput_writelock::addTextEvent( std::string *stxt )
    {
        this->p->addTextEvent( stxt );
    }

    //add event
    void dpinput_writelock::addEvent( dpinput_event *e )
    {
        this->p->addEvent( e );
    }

}








