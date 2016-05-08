
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

    //return z
    unsigned int dprender_gui_readlock::getZ( void )
    {
        return this->p->getZ();
    }

}







