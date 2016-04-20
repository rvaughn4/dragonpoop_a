/*
represents the lifecycle of a writelock on a dpwindow
this object is returned from a dpwindow when writelocked
deleting this object releases the writelock on the dpwindow
*/

#ifndef dpwindow_writelock_h
#define dpwindow_writelock_h

#include "../../dpinput/dpinput_writelock.h"

namespace dp
{

    class dpwindow;

    class dpwindow_writelock : public dpinput_writelock
    {

    private:

        dpwindow *p;

    protected:

        //dtor
        virtual ~dpwindow_writelock( void );

    public:

        //ctor
        dpwindow_writelock( dpwindow *p, dpmutex_writelock *ml );
        //returns true if open
        bool isOpen( void );
        //return width
        unsigned int getWidth( void );
        //return height
        unsigned int getHeight( void );
        //show window
        bool show( void );
        //hide window
        bool hide( void );
        //returns true if window is shown
        bool isShown( void );
        //make window fullscreen
        bool fullscreen( void );
        //make window windowed
        bool windowed( void );
        //returns true if window is fullscreen
        bool isFullscreen( void );

    };

}

#endif






