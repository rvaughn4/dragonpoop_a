
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

}







