/*
represents the lifecycle of a writelock on a dpapi
this object is returned from a dpapi when writelocked
deleting this object releases the writelock on the dpapi
*/

#ifndef dpapi_opengl1o5_writelock_h
#define dpapi_opengl1o5_writelock_h

#include "../../dpapi/dpapi/dpapi_writelock.h"

namespace dp
{

    class dpapi_opengl1o5;

    class dpapi_opengl1o5_writelock : public dpapi_writelock
    {

        dpapi_opengl1o5 *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_writelock( void );

    public:

        //ctor
        dpapi_opengl1o5_writelock( dpapi_opengl1o5 *p, dpmutex_writelock *ml );

    };

}

#endif








