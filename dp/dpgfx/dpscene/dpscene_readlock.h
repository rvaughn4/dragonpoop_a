/*
*/

#ifndef dpscene_readlock_h
#define dpscene_readlock_h

#include "../../dpcore/dptask/dptask_readlock.h"

namespace dp
{

    class dpscene;
    class dpgui;

    class dpscene_readlock : public dptask_readlock
    {

    private:

        dpscene *p;

    protected:

        //dtor
        virtual ~dpscene_readlock( void );

    public:

        //ctor
        dpscene_readlock( dpscene *p, dpmutex_readlock *ml );
        //return root gui
        dpgui *getGui( void );

    };

}

#endif





