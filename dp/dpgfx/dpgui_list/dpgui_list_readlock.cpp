
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

    //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
    unsigned int dpgui_list_readlock::getGuis( dpgui **glist, unsigned int max_cnt )
    {
        return this->p->getGuis( glist, max_cnt );
    }

    //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
    unsigned int dpgui_list_readlock::getGuisZSorted( dpgui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted )
    {
        return this->p->getGuisZSorted( glist, max_cnt, p_max_z, bInverted );
    }

}







