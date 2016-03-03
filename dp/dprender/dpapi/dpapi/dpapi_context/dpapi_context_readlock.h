/*
represents the lifecycle of a readlock on a dpapi_context
this object is returned from a dpapi_context when readlocked
deleting this object releases the readlock on the dpapi_context
*/

#ifndef dpapi_context_readlock_h
#define dpapi_context_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_context;
    class dpmutex_readlock;
    class dpapi_context_ref;

    class dpapi_context_readlock : public dpshared_readlock
    {

        dpapi_context *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_context_readlock( void );

    public:

        //ctor
        dpapi_context_readlock( dpapi_context *p, dpmutex_readlock *ml );

    };

}

#endif







