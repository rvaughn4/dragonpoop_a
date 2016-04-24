
/*
*/

#ifndef dpgui_writelock_h
#define dpgui_writelock_h

#include "../dpgui_list/dpgui_list_writelock.h"

namespace dp
{

    class dpgui;
    class dpbitmap;
    class dpinput;

    class dpgui_writelock : public dpgui_list_writelock
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
        //return z
        unsigned int getZ( void );
        //set z
        void setZ( unsigned int z );
        //returns bg bitmap
        dpbitmap *getBg( void );
        //returns fg bitmap
        dpbitmap *getFg( void );
        //attach renderer input
        void attachInput( dpinput *i );

    };

}

#endif






