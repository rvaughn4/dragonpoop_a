 /*
represents the lifecycle of a readlock on a dpapi_indexbuffer
this object is returned from a dpapi_indexbuffer when readlocked
deleting this object releases the readlock on the dpapi_indexbuffer
*/

#ifndef dpapi_indexbuffer_readlock_h
#define dpapi_indexbuffer_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_indexbuffer;

    class dpapi_indexbuffer_readlock : public dpshared_readlock
    {

        dpapi_indexbuffer *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_indexbuffer_readlock( void );

    public:

        //ctor
        dpapi_indexbuffer_readlock( dpapi_indexbuffer *p, dpmutex_readlock *ml );

    };

}

#endif









