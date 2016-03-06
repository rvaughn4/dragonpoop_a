 /*
represents the lifecycle of a writelock on a dpapi_renderpass
this object is returned from a dpapi_renderpass when writelocked
deleting this object releases the writelock on the dpapi_renderpass
*/

#ifndef dpapi_renderpass_writelock_h
#define dpapi_renderpass_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_renderpass;
    class dpmutex_writelock;
    class dpapi_renderpass_ref;

    class dpapi_renderpass_writelock : public dpshared_writelock
    {

    private:

        dpapi_renderpass *p;

    protected:

        //dtor
        virtual ~dpapi_renderpass_writelock( void );

    public:

        //ctor
        dpapi_renderpass_writelock( dpapi_renderpass *p, dpmutex_writelock *ml );

    };

}

#endif









