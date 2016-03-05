/*
represents the lifecycle of a readlock on a dpapi
this object is returned from a dpapi when readlocked
deleting this object releases the readlock on the dpapi
*/

#ifndef dpapi_opengl1o5_readlock_h
#define dpapi_opengl1o5_readlock_h

#include "../../dpapi/dpapi/dpapi_readlock.h"

namespace dp
{

    class dpapi_opengl1o5;

    class dpapi_opengl1o5_readlock : public dpapi_readlock
    {

        dpapi_opengl1o5 *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_readlock( void );

    public:

        //ctor
        dpapi_opengl1o5_readlock( dpapi_opengl1o5 *p, dpmutex_readlock *ml );

    };

}

#endif







