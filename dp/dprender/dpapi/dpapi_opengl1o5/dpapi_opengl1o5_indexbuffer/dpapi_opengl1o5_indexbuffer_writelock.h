 /*
represents the lifecycle of a writelock on a dpapi_opengl1o5_indexbuffer
this object is returned from a dpapi_opengl1o5_indexbuffer when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_indexbuffer
*/

#ifndef dpapi_opengl1o5_indexbuffer_writelock_h
#define dpapi_opengl1o5_indexbuffer_writelock_h

#include "../../dpapi/dpapi_indexbuffer/dpapi_indexbuffer_writelock.h"

namespace dp
{

    class dpapi_opengl1o5_indexbuffer;
    class dpindexbuffer;

    class dpapi_opengl1o5_indexbuffer_writelock : public dpapi_indexbuffer_writelock
    {

    private:

        dpapi_opengl1o5_indexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_indexbuffer_writelock( void );

    public:

        //ctor
        dpapi_opengl1o5_indexbuffer_writelock( dpapi_opengl1o5_indexbuffer *p, dpmutex_writelock *ml );
        //return ibo
        unsigned int getIBO( void );
        //return ib
        dpindexbuffer *getIB( void );
        //return count
        unsigned int getCount( void );

    };

}

#endif













