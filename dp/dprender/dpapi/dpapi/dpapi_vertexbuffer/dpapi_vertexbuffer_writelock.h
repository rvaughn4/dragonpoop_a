 /*
represents the lifecycle of a writelock on a dpapi_vertexbuffer
this object is returned from a dpapi_vertexbuffer when writelocked
deleting this object releases the writelock on the dpapi_vertexbuffer
*/

#ifndef dpapi_vertexbuffer_writelock_h
#define dpapi_vertexbuffer_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_vertexbuffer;

    class dpapi_vertexbuffer_writelock : public dpshared_writelock
    {

    private:

        dpapi_vertexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_vertexbuffer_writelock( void );

    public:

        //ctor
        dpapi_vertexbuffer_writelock( dpapi_vertexbuffer *p, dpmutex_writelock *ml );

    };

}

#endif











