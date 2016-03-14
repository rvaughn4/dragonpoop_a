 /*
represents the lifecycle of a readlock on a dpapi_texture
this object is returned from a dpapi_texture when readlocked
deleting this object releases the readlock on the dpapi_texture
*/

#ifndef dpapi_texture_readlock_h
#define dpapi_texture_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_texture;

    class dpapi_texture_readlock : public dpshared_readlock
    {

    private:

        dpapi_texture *p;

    protected:

        //dtor
        virtual ~dpapi_texture_readlock( void );

    public:

        //ctor
        dpapi_texture_readlock( dpapi_texture *p, dpmutex_readlock *ml );

    };

}

#endif









