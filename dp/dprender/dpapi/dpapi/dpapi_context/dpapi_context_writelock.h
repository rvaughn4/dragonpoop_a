 /*
represents the lifecycle of a writelock on a dpapi_context
this object is returned from a dpapi_context when writelocked
deleting this object releases the writelock on the dpapi_context
*/

#ifndef dpapi_context_writelock_h
#define dpapi_context_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_context;
    class dpmutex_writelock;
    class dpapi_context_ref;

    class dpapi_context_writelock : public dpshared_writelock
    {

    private:

        dpapi_context *p;

    protected:

        //dtor
        virtual ~dpapi_context_writelock( void );

    public:

        //ctor
        dpapi_context_writelock( dpapi_context *p, dpmutex_writelock *ml );

    };

}

#endif








