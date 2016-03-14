 /*
represents the lifecycle of a writelock on a dpapi_shader
this object is returned from a dpapi_shader when writelocked
deleting this object releases the writelock on the dpapi_shader
*/

#ifndef dpapi_shader_writelock_h
#define dpapi_shader_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_shader;

    class dpapi_shader_writelock : public dpshared_writelock
    {

    private:

        dpapi_shader *p;

    protected:

        //dtor
        virtual ~dpapi_shader_writelock( void );

    public:

        //ctor
        dpapi_shader_writelock( dpapi_shader *p, dpmutex_writelock *ml );

    };

}

#endif










