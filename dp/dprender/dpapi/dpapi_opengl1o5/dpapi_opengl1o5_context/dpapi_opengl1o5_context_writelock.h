/*
represents the lifecycle of a writelock on a dpapi_opengl1o5_context
this object is returned from a dpapi_opengl1o5_context when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_context
*/

#ifndef dpapi_opengl1o5_context_writelock_h
#define dpapi_opengl1o5_context_writelock_h

#include "../../dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi_context/dpapi_context.h"

namespace dp
{

    class dpapi_opengl1o5_context;
    class dpmutex_writelock;
    class dpapi_opengl1o5_context_ref;

    class dpapi_opengl1o5_context_writelock : public dpapi_context_writelock
    {

        dpapi_opengl1o5_context *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_context_writelock( void );

    public:

        //ctor
        dpapi_opengl1o5_context_writelock( dpapi_opengl1o5_context *p, dpmutex_writelock *ml );
        //make this context active in this thread
        bool makeActive( void );

    };

}

#endif









