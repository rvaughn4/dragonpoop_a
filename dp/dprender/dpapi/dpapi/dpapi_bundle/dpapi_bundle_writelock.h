 /*
represents the lifecycle of a writelock on a dpapi_bundle
this object is returned from a dpapi_bundle when writelocked
deleting this object releases the writelock on the dpapi_bundle
*/

#ifndef dpapi_bundle_writelock_h
#define dpapi_bundle_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_bundle;

    class dpapi_bundle_writelock : public dpshared_writelock
    {

    private:

        dpapi_bundle *p;

    protected:

        //dtor
        virtual ~dpapi_bundle_writelock( void );

    public:

        //ctor
        dpapi_bundle_writelock( dpapi_bundle *p, dpmutex_writelock *ml );

    };

}

#endif









