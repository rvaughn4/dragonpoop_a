/*
represents the lifecycle of a writelock on a dpshared
this object is returned from a dpshared when writelocked
deleting this object releases the writelock on the dpshared
*/

#ifndef dpbuffer_shared_writelock_h
#define dpbuffer_shared_writelock_h

#include "../../dpshared/dpshared_writelock.h"
#include "../dpbuffer_wrapper/dpbuffer_wrapper.h"

namespace dp
{

    class dpbuffer_shared;

    class dpbuffer_shared_writelock : public dpbuffer_wrapper, public dpshared_writelock
    {

    private:

        dpbuffer_shared *p;

    protected:

        //dtor
        virtual ~dpbuffer_shared_writelock( void );

    public:

        //ctor
        dpbuffer_shared_writelock( dpbuffer_shared *p, dpmutex_writelock *ml );

        friend class dpbuffer_shared;
    };

}

#endif




