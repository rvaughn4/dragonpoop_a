/*
represents the lifecycle of a writelock on a dpwindow
this object is returned from a dpwindow when writelocked
deleting this object releases the writelock on the dpwindow
*/

#ifndef dpwindow_writelock_h
#define dpwindow_writelock_h

#include "../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpwindow;
    class dpmutex_writelock;
    class dpwindow_ref;

    class dpwindow_writelock : public dpshared_writelock
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

    };

}

#endif






