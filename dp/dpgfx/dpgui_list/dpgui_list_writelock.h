
/*
*/

#ifndef dpgui_list_writelock_h
#define dpgui_list_writelock_h

#include "../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dpgui_list;
    class dpgui;

    class dpgui_list_writelock : public dptask_writelock
    {

        dpgui_list *p;

    private:

    protected:

        //dtor
        virtual ~dpgui_list_writelock( void );

    public:

        //ctor
        dpgui_list_writelock( dpgui_list *p, dpmutex_writelock *ml );
        //add gui, starts task and takes ownership of gui, sets pointer to zero, use a ref to access
        bool addGui( dpgui **ngui, bool bMakeFront );
        //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
        unsigned int getGuis( dpgui **glist, unsigned int max_cnt );
        //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
        unsigned int getGuisZSorted( dpgui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted );

    };

}

#endif







