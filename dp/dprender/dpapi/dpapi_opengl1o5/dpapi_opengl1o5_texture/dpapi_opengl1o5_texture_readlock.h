 /*
represents the lifecycle of a readlock on a dpapi_opengl1o5_texture
this object is returned from a dpapi_opengl1o5_texture when readlocked
deleting this object releases the readlock on the dpapi_opengl1o5_texture
*/

#ifndef dpapi_opengl1o5_texture_readlock_h
#define dpapi_opengl1o5_texture_readlock_h

#include "../../dpapi/dpapi_texture/dpapi_texture_readlock.h"

namespace dp
{

    class dpapi_opengl1o5_texture;

    class dpapi_opengl1o5_texture_readlock : public dpapi_texture_readlock
    {

    private:

        dpapi_opengl1o5_texture *p;

    protected:

        //dtor
        virtual ~dpapi_opengl1o5_texture_readlock( void );

    public:

        //ctor
        dpapi_opengl1o5_texture_readlock( dpapi_opengl1o5_texture *p, dpmutex_readlock *ml );

    };

}

#endif










