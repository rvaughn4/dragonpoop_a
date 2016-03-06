/*
represents the lifecycle of a readlock on a dpapi_opengl1o5_context
this object is returned from a dpapi_opengl1o5_context when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_context
*/

#ifndef dpapi_opengl1o5_context_readlock_h
#define dpapi_opengl1o5_context_readlock_h

#include "../../dpapi/dpapi_context/dpapi_context_readlock.h"
#include "../../dpapi/dpapi_context/dpapi_context.h"

namespace dp
{

    class dpapi_opengl1o5_context;
    class dpmutex_readlock;
    class dpapi_opengl1o5_context_ref;

    class dpapi_opengl1o5_context_readlock : public dpapi_context_readlock
    {

        dpapi_opengl1o5_context *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_context_readlock( void );

    public:

        //ctor
        dpapi_opengl1o5_context_readlock( dpapi_opengl1o5_context *p, dpmutex_readlock *ml );

    };

}

#endif








