 /*
represents the lifecycle of a writelock on a dpapi_material
this object is returned from a dpapi_material when writelocked
deleting this object releases the writelock on the dpapi_material
*/

#ifndef dpapi_material_writelock_h
#define dpapi_material_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_material;

    class dpapi_material_writelock : public dpshared_writelock
    {

    private:

        dpapi_material *p;

    protected:

        //dtor
        virtual ~dpapi_material_writelock( void );

    public:

        //ctor
        dpapi_material_writelock( dpapi_material *p, dpmutex_writelock *ml );

    };

}

#endif










