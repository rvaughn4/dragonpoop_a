
/*
*/

#ifndef dprender_gui_readlock_h
#define dprender_gui_readlock_h

#include "../dprender_gui_list/dprender_gui_list_readlock.h"

namespace dp
{

    class dprender_gui;

    class dprender_gui_readlock : public dprender_gui_list_readlock
    {

        dprender_gui *p;

    private:

    protected:

        //dtor
        virtual ~dprender_gui_readlock( void );

    public:

        //ctor
        dprender_gui_readlock( dprender_gui *p, dpmutex_readlock *ml );
        //get dimensions
        void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        void getPosition( int *x, int *y );
        //return z
        unsigned int getZ( void );

    };

}

#endif






