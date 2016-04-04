
/*
*/

#ifndef dpgui_list_writelock_h
#define dpgui_list_writelock_h

#include "../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dpgui_list;

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

    };

}

#endif







