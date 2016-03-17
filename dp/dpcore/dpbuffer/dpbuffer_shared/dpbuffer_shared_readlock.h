/*
represents the lifecycle of a readlock on a dpshared
this object is returned from a dpshared when readlocked
deleting this object releases the readlock on the dpshared
*/

#ifndef dpbuffer_shared_readlock_h
#define dpbuffer_shared_readlock_h

#include "../../dpshared/dpshared_readlock.h"
#include "../dpbuffer_wrapper/dpbuffer_wrapper.h"

namespace dp
{

    class dpbuffer_shared;

    class dpbuffer_shared_readlock : public dpbuffer_wrapper, public dpshared_readlock
    {

    private:

        dpbuffer_shared *p;

    protected:

        //dtor
        virtual ~dpbuffer_shared_readlock( void );

    public:

        //ctor
        dpbuffer_shared_readlock( dpbuffer_shared *p, dpmutex_readlock *ml );

        friend class dpbuffer_shared;
    };

}

#endif



