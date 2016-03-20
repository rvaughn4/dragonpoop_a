 /*
represents the lifecycle of a readlock on a dpapi_opengl1o5_indexbuffer
this object is returned from a dpapi_opengl1o5_indexbuffer when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_indexbuffer
*/

#ifndef dpapi_opengl1o5_indexbuffer_readlock_h
#define dpapi_opengl1o5_indexbuffer_readlock_h

#include "../../dpapi/dpapi_indexbuffer/dpapi_indexbuffer_readlock.h"

namespace dp
{

    class dpapi_opengl1o5_indexbuffer;

    class dpapi_opengl1o5_indexbuffer_readlock : public dpapi_indexbuffer_readlock
    {

    private:

        dpapi_opengl1o5_indexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_indexbuffer_readlock( void );

    public:

        //ctor
        dpapi_opengl1o5_indexbuffer_readlock( dpapi_opengl1o5_indexbuffer *p, dpmutex_readlock *ml );

    };

}

#endif












