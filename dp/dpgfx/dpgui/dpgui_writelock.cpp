
 /*
*/

#include "dpgui_writelock.h"
#include "dpgui.h"

namespace dp
{

    //ctor
    dpgui_writelock::dpgui_writelock( dpgui *p, dpmutex_writelock *ml ) : dpgui_list_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpgui_writelock::~dpgui_writelock( void )
    {

    }

    //set dimensions
    void dpgui_writelock::setDimensions( unsigned int w, unsigned int h )
    {
        this->p->setDimensions( w, h );
    }

    //set position
    void dpgui_writelock::setPosition( int x, int y )
    {
        this->p->setPosition( x, y );
    }

    //get dimensions
    void dpgui_writelock::getDimensions( unsigned int *w, unsigned int *h )
    {
        this->p->getDimensions( w, h );
    }

    //get position
    void dpgui_writelock::getPosition( int *x, int *y )
    {
        this->p->getPosition( x, y );
    }

    //force bg to be redrawn
    void dpgui_writelock::redrawBg( void )
    {
        this->p->redrawBg();
    }

    //force fg to be redrawn
    void dpgui_writelock::redrawFg( void )
    {
        this->p->redrawFg();
    }

    //return z
    unsigned int dpgui_writelock::getZ( void )
    {
        return this->p->getZ();
    }

    //set z
    void dpgui_writelock::setZ( unsigned int z )
    {
        this->p->setZ( z );
    }

    //returns bg bitmap
    dpbitmap *dpgui_writelock::getBg( void )
    {
        return this->p->getBg();
    }

    //returns fg bitmap
    dpbitmap *dpgui_writelock::getFg( void )
    {
        return this->p->getFg();
    }

    //attach renderer input
    void dpgui_writelock::attachInput( dpinput *i )
    {
        this->p->attachInput( i );
    }

    //return true if centered
    bool dpgui_writelock::isCentered( void )
    {
        return this->p->isCentered();
    }

    //set centered mode
    void dpgui_writelock::setCentered( bool b )
    {
        this->p->setCentered( b );
    }

    //return true if floating
    bool dpgui_writelock::isFloating( void )
    {
        return this->p->isFloating();
    }

    //set floating mode
    void dpgui_writelock::setFloating( bool b )
    {
        this->p->setFloating( b );
    }

    //return true if follows cursor
    bool dpgui_writelock::isFollowingCursor( void )
    {
        return this->p->isFollowingCursor();
    }

    //set cursor following mode
    void dpgui_writelock::setFollowingCursor( bool b )
    {
        this->p->setFollowingCursor( b );
    }

    //get rotation
    void dpgui_writelock::getRotation( dpxyzw *p )
    {
        this->p->getRotation( p );
    }

    //set rotation
    void dpgui_writelock::setRotation( dpxyzw *p )
    {
        this->p->setRotation( p );
    }

    //get spin
    void dpgui_writelock::getSpin( dpxyzw *p )
    {
        this->p->getSpin( p );
    }

    //set spin
    void dpgui_writelock::setSpin( dpxyzw *p )
    {
        this->p->setSpin( p );
    }

    //returns true if grows when mouse hovers over
    bool dpgui_writelock::doesGrow( void )
    {
        return this->p->doesGrow();
    }

    //set mouse hover mode
    void dpgui_writelock::setGrow( bool b )
    {
        this->p->setGrow( b );
    }

    //returns true if minimized
    bool dpgui_writelock::isMinimized( void )
    {
        return this->p->isMinimized();
    }

    //set minimized
    void dpgui_writelock::setMinimized( bool b )
    {
        this->p->setMinimized( b );
    }

}







