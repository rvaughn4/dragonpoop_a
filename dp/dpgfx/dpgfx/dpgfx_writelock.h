/*
represents the lifecycle of a writelock on a dpgfx
this object is returned from a dpgfx when writelocked
deleting this object releases the writelock on the dpgfx
*/

#ifndef dpgfx_writelock_h
#define dpgfx_writelock_h

#include "../../dpcore/dptask/dptask_writelock.h"

namespace dp
{

    class dpgfx;
    class dpscene;

    class dpgfx_writelock : public dptask_writelock
    {

    private:

        dpgfx *p;

    protected:

        //dtor
        virtual ~dpgfx_writelock( void );

    public:

        //ctor
        dpgfx_writelock( dpgfx *p, dpmutex_writelock *ml );
        //add scene
        bool addScene( dpscene **s );

    };

}

#endif







