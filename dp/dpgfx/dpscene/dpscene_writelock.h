/*
*/

#ifndef dpscene_writelock_h
#define dpscene_writelock_h

#include "../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dpscene;
    class dpgui;

    class dpscene_writelock : public dptask_writelock
    {

    private:

        dpscene *p;

    protected:

        //dtor
        virtual ~dpscene_writelock( void );

    public:

        //ctor
        dpscene_writelock( dpscene *p, dpmutex_writelock *ml );
        //return root gui
        dpgui *getGui( void );

    };

}

#endif






