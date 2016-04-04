
/*
*/

#ifndef dpgui_readlock_h
#define dpgui_readlock_h

#include "../../dpcore/dptask/dptask_readlock.h"

namespace dp
{

    class dpgui;

    class dpgui_readlock : public dptask_readlock
    {

        dpgui *p;

    private:

    protected:

        //dtor
        virtual ~dpgui_readlock( void );

    public:

        //ctor
        dpgui_readlock( dpgui *p, dpmutex_readlock *ml );
        //get dimensions
        void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        void getPosition( int *x, int *y );

    };

}

#endif





