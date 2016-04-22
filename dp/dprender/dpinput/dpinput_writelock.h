/*
represents the lifecycle of a writelock on a dpinput
this object is returned from a dpinput when writelocked
deleting this object releases the writelock on the dpinput
*/

#ifndef dpinput_writelock_h
#define dpinput_writelock_h

#include "../../dpcore/dpshared/dpshared_writelock.h"
#include "dpinput.h"

namespace dp
{

    class dpinput;
    struct dpinput_event;

    class dpinput_writelock : public dpshared_writelock
    {

        dpinput *p;

    private:

    protected:

        //dtor
        virtual ~dpinput_writelock( void );

    public:

        //ctor
        dpinput_writelock( dpinput *p, dpmutex_writelock *ml );
        //get events newer than time
        unsigned int getEvents( dpinput_event **elist, unsigned int max_sz, uint64_t t );
        //add mouse event
        void addMouseEvent( float x, float y, float sx, float sy, bool bIsRight, bool bIsDown );
        //add keypress event
        void addKeyPressEvent( bool bIsDown, std::string *sname );
        //add text event
        void addTextEvent( std::string *stxt );
        //add event
        void addEvent( dpinput_event *e );

    };

}

#endif







