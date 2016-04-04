
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

}






