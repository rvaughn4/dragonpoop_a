
 /*
*/

#include "dpgui_list_writelock.h"
#include "dpgui_list.h"

namespace dp
{

    //ctor
    dpgui_list_writelock::dpgui_list_writelock( dpgui_list *p, dpmutex_writelock *ml ) : dptask_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dpgui_list_writelock::~dpgui_list_writelock( void )
    {

    }

}








