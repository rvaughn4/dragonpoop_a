 /*
represents the lifecycle of a writelock on a dpapi_indexbuffer
this object is returned from a dpapi_indexbuffer when writelocked
deleting this object releases the writelock on the dpapi_indexbuffer
*/

#ifndef dpapi_indexbuffer_writelock_h
#define dpapi_indexbuffer_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_indexbuffer;

    class dpapi_indexbuffer_writelock : public dpshared_writelock
    {

    private:

        dpapi_indexbuffer *p;

    protected:

        //dtor
        virtual ~dpapi_indexbuffer_writelock( void );

    public:

        //ctor
        dpapi_indexbuffer_writelock( dpapi_indexbuffer *p, dpmutex_writelock *ml );

    };

}

#endif










