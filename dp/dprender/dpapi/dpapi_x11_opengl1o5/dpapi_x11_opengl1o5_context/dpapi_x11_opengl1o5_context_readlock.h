/*
represents the lifecycle of a readlock on a dpapi_opengl1o5_context
this object is returned from a dpapi_opengl1o5_context when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_context
*/

#ifndef dpapi_x11_opengl1o5_context_readlock_h
#define dpapi_x11_opengl1o5_context_readlock_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5_context/dpapi_opengl1o5_context_readlock.h"
#include "../../dpapi_opengl1o5/dpapi_opengl1o5_context/dpapi_opengl1o5_context.h"

namespace dp
{

    class dpapi_x11_opengl1o5_context;

    class dpapi_x11_opengl1o5_context_readlock : public dpapi_opengl1o5_context_readlock
    {

        dpapi_x11_opengl1o5_context *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_x11_opengl1o5_context_readlock( void );

    public:

        //ctor
        dpapi_x11_opengl1o5_context_readlock( dpapi_x11_opengl1o5_context *p, dpmutex_readlock *ml );

    };

}

#endif








