
/*
*/

#ifndef dpgui_list_readlock_h
#define dpgui_list_readlock_h

#include "../../dpcore/dptask/dptask_readlock.h"

namespace dp
{

    class dpgui_list;
    class dpgui;

    class dpgui_list_readlock : public dptask_readlock
    {

        dpgui_list *p;

    private:

    protected:

        //dtor
        virtual ~dpgui_list_readlock( void );

    public:

        //ctor
        dpgui_list_readlock( dpgui_list *p, dpmutex_readlock *ml );
        //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
        unsigned int getGuis( dpgui **glist, unsigned int max_cnt );
        //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
        unsigned int getGuisZSorted( dpgui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted );

    };

}

#endif






