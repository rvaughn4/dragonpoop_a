
/*
*/

#ifndef dpgui_writelock_h
#define dpgui_writelock_h

#include "../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dpgui;

    class dpgui_writelock : public dptask_writelock
    {

        dpgui *p;

    private:

    protected:

        //dtor
        virtual ~dpgui_writelock( void );

    public:

        //ctor
        dpgui_writelock( dpgui *p, dpmutex_writelock *ml );
        //set dimensions
        void setDimensions( unsigned int w, unsigned int h );
        //set position
        void setPosition( int x, int y );
        //get dimensions
        void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        void getPosition( int *x, int *y );
        //force bg to be redrawn
        void redrawBg( void );
        //force fg to be redrawn
        void redrawFg( void );

    };

}

#endif






