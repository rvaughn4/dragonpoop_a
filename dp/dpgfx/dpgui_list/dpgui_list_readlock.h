
/*
*/

#ifndef dpgui_list_readlock_h
#define dpgui_list_readlock_h

#include "../../dpcore/dptask/dptask_readlock.h"

namespace dp
{

    class dpgui_list;

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

    };

}

#endif






