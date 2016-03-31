 /*
represents the lifecycle of a writelock on a dpapi_opengl1o5_texture
this object is returned from a dpapi_opengl1o5_texture when writelocked
deleting this object releases the writelock on the dpapi_opengl1o5_texture
*/

#ifndef dpapi_opengl1o5_texture_writelock_h
#define dpapi_opengl1o5_texture_writelock_h

#include "../../dpapi/dpapi_texture/dpapi_texture_writelock.h"

namespace dp
{

    class dpapi_opengl1o5_texture;

    class dpapi_opengl1o5_texture_writelock : public dpapi_texture_writelock
    {

    private:

        dpapi_opengl1o5_texture *p;

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_texture_writelock( void );

    public:

        //ctor
        dpapi_opengl1o5_texture_writelock( dpapi_opengl1o5_texture *p, dpmutex_writelock *ml );

    };

}

#endif











