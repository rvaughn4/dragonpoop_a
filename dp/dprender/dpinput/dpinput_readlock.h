/*
represents the lifecycle of a readlock on a dpinput
this object is returned from a dpinput when readlocked
deleting this object releases the readlock on the dpinput
*/

#ifndef dpinput_readlock_h
#define dpinput_readlock_h

#include "../../dpcore/dpshared/dpshared_readlock.h"
#include "dpinput.h"

namespace dp
{

    class dpinput;
    struct dpinput_event;

    class dpinput_readlock : public dpshared_readlock
    {

        dpinput *p;

    private:

    protected:

        //dtor
        virtual ~dpinput_readlock( void );

    public:

        //ctor
        dpinput_readlock( dpinput *p, dpmutex_readlock *ml );
        //get events newer than time
        unsigned int getEvents( dpinput_event **elist, unsigned int max_sz, uint64_t t );

    };

}

#endif






