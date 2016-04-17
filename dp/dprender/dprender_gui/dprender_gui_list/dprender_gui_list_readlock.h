
/*
*/

#ifndef dprender_gui_list_readlock_h
#define dprender_gui_list_readlock_h

#include "../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dprender_gui_list;
    class dprender_gui;

    class dprender_gui_list_readlock : public dpshared_readlock
    {

        dprender_gui_list *p;

    private:

    protected:

        //dtor
        virtual ~dprender_gui_list_readlock( void );

    public:

        //ctor
        dprender_gui_list_readlock( dprender_gui_list *p, dpmutex_readlock *ml );
        //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
        unsigned int getGuis( dprender_gui **glist, unsigned int max_cnt );
        //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
        unsigned int getGuisZSorted( dprender_gui **glist, unsigned int max_cnt, unsigned int *p_max_z, bool bInverted );

    };

}

#endif







