/*
represents the lifecycle of a readlock on a dpapi_renderpass
this object is returned from a dpapi_renderpass when readlocked
deleting this object releases the readlock on the dpapi_renderpass
*/

#ifndef dpapi_renderpass_readlock_h
#define dpapi_renderpass_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_renderpass;

    class dpapi_renderpass_readlock : public dpshared_readlock
    {

        dpapi_renderpass *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_renderpass_readlock( void );

    public:

        //ctor
        dpapi_renderpass_readlock( dpapi_renderpass *p, dpmutex_readlock *ml );

    };

}

#endif








