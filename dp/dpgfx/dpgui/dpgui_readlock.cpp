
 /*
*/

#include "dpgui_readlock.h"
#include "dpgui.h"

namespace dp
{

    //ctor
    dpgui_readlock::dpgui_readlock( dpgui *p, dpmutex_readlock *ml ) : dpgui_list_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpgui_readlock::~dpgui_readlock( void )
    {

    }

    //get dimensions
    void dpgui_readlock::getDimensions( unsigned int *w, unsigned int *h )
    {
        this->p->getDimensions( w, h );
    }

    //get position
    void dpgui_readlock::getPosition( int *x, int *y )
    {
        this->p->getPosition( x, y );
    }

    //return z
    unsigned int dpgui_readlock::getZ( void )
    {
        return this->p->getZ();
    }

    //returns bg bitmap
    dpbitmap_32bit_uncompressed *dpgui_readlock::getBg( void )
    {
        return this->p->getBg();
    }

    //returns fg bitmap
    dpbitmap_32bit_uncompressed *dpgui_readlock::getFg( void )
    {
        return this->p->getFg();
    }

    //return bg time
    unsigned int dpgui_readlock::getBgTime( void )
    {
        return this->p->getBgTime();
    }

    //return fg time
    unsigned int dpgui_readlock::getFgTime( void )
    {
        return this->p->getFgTime();
    }

    //return size time
    unsigned int dpgui_readlock::getSzTime( void )
    {
        return this->p->getSzTime();
    }

    //return true if centered
    bool dpgui_readlock::isCentered( void )
    {
        return this->p->isCentered();
    }

    //return true if floating
    bool dpgui_readlock::isFloating( void )
    {
        return this->p->isFloating();
    }

    //return true if follows cursor
    bool dpgui_readlock::isFollowingCursor( void )
    {
        return this->p->isFollowingCursor();
    }

    //get rotation
    void dpgui_readlock::getRotation( dpxyzw *p )
    {
        this->p->getRotation( p );
    }

    //get spin
    void dpgui_readlock::getSpin( dpxyzw *p )
    {
        this->p->getSpin( p );
    }

    //returns true if grows when mouse hovers over
    bool dpgui_readlock::doesGrow( void )
    {
        return this->p->doesGrow();
    }

    //returns true if minimized
    bool dpgui_readlock::isMinimized( void )
    {
        return this->p->isMinimized();
    }

    //get alignment
    unsigned int dpgui_readlock::getAlignment( void )
    {
        return this->p->getAlignment();
    }

    //get zoom
    float dpgui_readlock::getZoom( void )
    {
        return this->p->getZoom();
    }

    //returns true if horiz fill enabled
    bool dpgui_readlock::isHorizFill( void )
    {
        return this->p->isHorizFill();
    }

}






