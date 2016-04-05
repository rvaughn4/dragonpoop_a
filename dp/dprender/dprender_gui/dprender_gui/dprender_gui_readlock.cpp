
 /*
*/

#include "dprender_gui_readlock.h"
#include "dprender_gui.h"

namespace dp
{

    //ctor
    dprender_gui_readlock::dprender_gui_readlock( dprender_gui *p, dpmutex_readlock *ml ) : dprender_gui_list_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_gui_readlock::~dprender_gui_readlock( void )
    {

    }

    //get dimensions
    void dprender_gui_readlock::getDimensions( unsigned int *w, unsigned int *h )
    {
        this->p->getDimensions( w, h );
    }

    //get position
    void dprender_gui_readlock::getPosition( int *x, int *y )
    {
        this->p->getPosition( x, y );
    }

    //return z
    unsigned int dprender_gui_readlock::getZ( void )
    {
        return this->p->getZ();
    }

}







