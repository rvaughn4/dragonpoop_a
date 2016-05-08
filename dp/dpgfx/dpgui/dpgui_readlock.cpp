
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

    //get attributes
    void dpgui_readlock::getAttributes( dpgui_attribs *a )
    {
        this->p->getAttributes( a );
    }


}






