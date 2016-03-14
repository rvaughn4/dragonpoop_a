 /*
represents the lifecycle of a readlock on a dpapi_shader
this object is returned from a dpapi_shader when readlocked
deleting this object releases the readlock on the dpapi_shader
*/

#ifndef dpapi_shader_readlock_h
#define dpapi_shader_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_shader;

    class dpapi_shader_readlock : public dpshared_readlock
    {

    private:

        dpapi_shader *p;

    protected:

        //dtor
        virtual ~dpapi_shader_readlock( void );

    public:

        //ctor
        dpapi_shader_readlock( dpapi_shader *p, dpmutex_readlock *ml );

    };

}

#endif









