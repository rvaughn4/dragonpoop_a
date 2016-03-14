 /*
represents the lifecycle of a writelock on a dpapi_texture
this object is returned from a dpapi_texture when writelocked
deleting this object releases the writelock on the dpapi_texture
*/

#ifndef dpapi_texture_writelock_h
#define dpapi_texture_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_texture;

    class dpapi_texture_writelock : public dpshared_writelock
    {

    private:

        dpapi_texture *p;

    protected:

        //dtor
        virtual ~dpapi_texture_writelock( void );

    public:

        //ctor
        dpapi_texture_writelock( dpapi_texture *p, dpmutex_writelock *ml );

    };

}

#endif










