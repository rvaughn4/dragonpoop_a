 /*
represents the lifecycle of a readlock on a dpapi_opengl1o5_vertexbuffer
this object is returned from a dpapi_opengl1o5_vertexbuffer when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_vertexbuffer
*/

#ifndef dpapi_opengl1o5_vertexbuffer_readlock_h
#define dpapi_opengl1o5_vertexbuffer_readlock_h

#include "../../dpapi/dpapi_vertexbuffer/dpapi_vertexbuffer_readlock.h"

namespace dp
{

    class dpapi_opengl1o5_vertexbuffer;

    class dpapi_opengl1o5_vertexbuffer_readlock : public dpapi_vertexbuffer_readlock
    {

    private:

        dpapi_opengl1o5_vertexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_vertexbuffer_readlock( void );

    public:

        //ctor
        dpapi_opengl1o5_vertexbuffer_readlock( dpapi_opengl1o5_vertexbuffer *p, dpmutex_readlock *ml );

    };

}

#endif











