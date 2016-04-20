/*
represents the lifecycle of a readlock on a dpwindow
this object is returned from a dpwindow when readlocked
deleting this object releases the readlock on the dpwindow
*/

#ifndef dpwindow_readlock_h
#define dpwindow_readlock_h

#include "../../dpinput/dpinput_readlock.h"

namespace dp
{

    class dpwindow;

    class dpwindow_readlock : public dpinput_readlock
    {

        dpwindow *p;

    private:

    protected:

        //dtor
        virtual ~dpwindow_readlock( void );

    public:

        //ctor
        dpwindow_readlock( dpwindow *p, dpmutex_readlock *ml );
        //returns true if open
        bool isOpen( void );
        //return width
        unsigned int getWidth( void );
        //return height
        unsigned int getHeight( void );
        //returns true if window is shown
        bool isShown( void );
        //returns true if window is fullscreen
        bool isFullscreen( void );

    };

}

#endif





