
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


    //returns bg bitmap
    dpbitmap_32bit_uncompressed *dpgui_writelock::getBg( void )
    {
        return this->p->getBg();
    }

    //returns fg bitmap
    dpbitmap_32bit_uncompressed *dpgui_writelock::getFg( void )
    {
        return this->p->getFg();
    }

    //attach renderer input
    void dpgui_writelock::attachInput( dpinput *i )
    {
        this->p->attachInput( i );
    }

    //zoom in
    void dpgui_writelock::zoomIn( void )
    {
        this->p->zoomIn();
    }

    //zoom out
    void dpgui_writelock::zoomOut( void )
    {
        this->p->zoomOut();
    }

    //get attributes
    void dpgui_writelock::getAttributes( dpgui_attribs *a )
    {
        this->p->getAttributes( a );
    }

    //set attributes
    void dpgui_writelock::setAttributes( dpgui_attribs *a )
    {
        this->p->setAttributes( a );
    }

}







