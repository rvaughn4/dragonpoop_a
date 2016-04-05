
 /*
*/

#include "dprender_gui_list_writelock.h"
#include "dprender_gui_list.h"

namespace dp
{

    //ctor
    dprender_gui_list_writelock::dprender_gui_list_writelock( dprender_gui_list *p, dpmutex_writelock *ml ) : dpshared_writelock( p, ml )
    {
        this->p = p;
    }

    //dtor
    dprender_gui_list_writelock::~dprender_gui_list_writelock( void )
    {

    }

    //add gui, starts task and takes ownership of gui, sets pointer to zero, use a ref to access
    bool dprender_gui_list_writelock::addGui( dprender_gui **ngui )
    {
        return this->p->addGui( ngui );
    }

    //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
    unsigned int dprender_gui_list_writelock::getGuis( dprender_gui **glist, unsigned int max_cnt )
    {
        return this->p->getGuis( glist, max_cnt );
    }

    //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
    unsigned int dprender_gui_list_writelock::getGuisZSorted( dprender_gui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted )
    {
        return this->p->getGuisZSorted( glist, max_cnt, p_max_z, bInverted );
    }

    //pass in context
    void dprender_gui_list_writelock::passContext( dpapi_context_writelock *ctx )
    {
        this->p->passContext( ctx );
    }

}









