 /*
represents the lifecycle of a readlock on a dpapi_material
this object is returned from a dpapi_material when readlocked
deleting this object releases the readlock on the dpapi_material
*/

#ifndef dpapi_material_readlock_h
#define dpapi_material_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_material;

    class dpapi_material_readlock : public dpshared_readlock
    {

        dpapi_material *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_material_readlock( void );

    public:

        //ctor
        dpapi_material_readlock( dpapi_material *p, dpmutex_readlock *ml );

    };

}

#endif









