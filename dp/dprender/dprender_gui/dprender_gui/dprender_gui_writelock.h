
/*
*/

#ifndef dprender_gui_writelock_h
#define dprender_gui_writelock_h

#include "../dprender_gui_list/dprender_gui_list_writelock.h"

namespace dp
{

    class dprender_gui;
    class dpapi_context_writelock;

    class dprender_gui_writelock : public dprender_gui_list_writelock
    {

        dprender_gui *p;

    private:

    protected:

        //dtor
        virtual ~dprender_gui_writelock( void );

    public:

        //ctor
        dprender_gui_writelock( dprender_gui *p, dpmutex_writelock *ml );
        //set dimensions
        void setDimensions( unsigned int w, unsigned int h );
        //set position
        void setPosition( int x, int y );
        //get dimensions
        void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        void getPosition( int *x, int *y );
        //return z
        unsigned int getZ( void );
        //set z
        void setZ( unsigned int z );
        //pass in context
        void passContext( dpapi_context_writelock *ctx );

    };

}

#endif







