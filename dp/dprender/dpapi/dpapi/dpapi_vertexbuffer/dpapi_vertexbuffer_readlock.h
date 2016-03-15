 /*
represents the lifecycle of a readlock on a dpapi_vertexbuffer
this object is returned from a dpapi_vertexbuffer when readlocked
deleting this object releases the readlock on the dpapi_vertexbuffer
*/

#ifndef dpapi_vertexbuffer_readlock_h
#define dpapi_vertexbuffer_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_vertexbuffer;

    class dpapi_vertexbuffer_readlock : public dpshared_readlock
    {

    private:

        dpapi_vertexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_vertexbuffer_readlock( void );

    public:

        //ctor
        dpapi_vertexbuffer_readlock( dpapi_vertexbuffer *p, dpmutex_readlock *ml );

    };

}

#endif










