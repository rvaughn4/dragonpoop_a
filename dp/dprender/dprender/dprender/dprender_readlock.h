/*
represents the lifecycle of a readlock on a dprender
this object is returned from a dprender when readlocked
deleting this object releases the readlock on the dprender
*/

#ifndef dprender_readlock_h
#define dprender_readlock_h

#include "../../../dpcore/dptask/dptask_readlock.h"

namespace dp
{

    class dprender;

    class dprender_readlock : public dptask_readlock
    {

        dprender *p;

    private:

    protected:

        //dtor
        virtual ~dprender_readlock( void );

    public:

        //ctor
        dprender_readlock( dprender *p, dpmutex_readlock *ml );

    };

}

#endif







