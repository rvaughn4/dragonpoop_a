/*
represents the lifecycle of a writelock on a dprender
this object is returned from a dprender when writelocked
deleting this object releases the writelock on the dprender
*/

#ifndef dprender_writelock_h
#define dprender_writelock_h

#include "../../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dprender;
    class dprender_scene;

    class dprender_writelock : public dptask_writelock
    {

        dprender *p;

    private:

    protected:

        //dtor
        virtual ~dprender_writelock( void );

    public:

        //ctor
        dprender_writelock( dprender *p, dpmutex_writelock *ml );

    };

}

#endif








