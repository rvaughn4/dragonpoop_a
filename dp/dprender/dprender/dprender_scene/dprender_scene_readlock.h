/*
represents the lifecycle of a readlock on a dprender_scene
this object is returned from a dprender_scene when readlocked
deleting this object releases the readlock on the dprender_scene
*/

#ifndef dprender_scene_readlock_h
#define dprender_scene_readlock_h

#include "../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dprender_scene;

    class dprender_scene_readlock : public dpshared_readlock
    {

        dprender_scene *p;

    private:

    protected:

        //dtor
        virtual ~dprender_scene_readlock( void );

    public:

        //ctor
        dprender_scene_readlock( dprender_scene *p, dpmutex_readlock *ml );

    };

}

#endif








