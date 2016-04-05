
 /*
*/

#include "dprender_gui_list_readlock.h"
#include "dprender_gui_list.h"

namespace dp
{

    //ctor
    dprender_gui_list_readlock::dprender_gui_list_readlock( dprender_gui_list *p, dpmutex_readlock *ml ) : dpshared_readlock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_gui_list_readlock::~dprender_gui_list_readlock( void )
    {

    }

    //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
    unsigned int dprender_gui_list_readlock::getGuis( dprender_gui **glist, unsigned int max_cnt )
    {
        return this->p->getGuis( glist, max_cnt );
    }

    //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
    unsigned int dprender_gui_list_readlock::getGuisZSorted( dprender_gui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted )
    {
        return this->p->getGuisZSorted( glist, max_cnt, p_max_z, bInverted );
    }

}








