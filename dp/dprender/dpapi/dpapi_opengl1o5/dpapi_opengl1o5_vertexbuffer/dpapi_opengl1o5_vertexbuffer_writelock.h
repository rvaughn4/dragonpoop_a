 /*
represents the lifecycle of a writelock on a dpapi_opengl1o5_vertexbuffer
this object is returned from a dpapi_opengl1o5_vertexbuffer when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_vertexbuffer
*/

#ifndef dpapi_opengl1o5_vertexbuffer_writelock_h
#define dpapi_opengl1o5_vertexbuffer_writelock_h

#include "../../dpapi/dpapi_vertexbuffer/dpapi_vertexbuffer_writelock.h"

namespace dp
{

    class dpapi_opengl1o5_vertexbuffer;
    class dpvertexbuffer;

    class dpapi_opengl1o5_vertexbuffer_writelock : public dpapi_vertexbuffer_writelock
    {

    private:

        dpapi_opengl1o5_vertexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_vertexbuffer_writelock( void );

    public:

        //ctor
        dpapi_opengl1o5_vertexbuffer_writelock( dpapi_opengl1o5_vertexbuffer *p, dpmutex_writelock *ml );
        //return vbo
        unsigned int getVBO( void );
        //return vb
        dpvertexbuffer *getVB( void );

    };

}

#endif












