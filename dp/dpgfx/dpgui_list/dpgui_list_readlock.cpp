
 /*
*/

#include "dpgui_list_readlock.h"
#include "dpgui_list.h"

namespace dp
{

    //ctor
    dpgui_list_readlock::dpgui_list_readlock( dpgui_list *p, dpmutex_readlock *ml ) : dptask_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpgui_list_readlock::~dpgui_list_readlock( void )
    {

    }

}







