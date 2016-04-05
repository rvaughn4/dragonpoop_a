
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

    //add gui, starts task and takes ownership of gui, sets pointer to zero, use a ref to access
    bool dpgui_list_writelock::addGui( dpgui **ngui, bool bMakeFront )
    {
        return this->p->addGui( ngui, bMakeFront );
    }

    //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
    unsigned int dpgui_list_writelock::getGuis( dpgui **glist, unsigned int max_cnt )
    {
        return this->p->getGuis( glist, max_cnt );
    }

    //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
    unsigned int dpgui_list_writelock::getGuisZSorted( dpgui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted )
    {
        return this->p->getGuisZSorted( glist, max_cnt, p_max_z, bInverted );
    }

}








