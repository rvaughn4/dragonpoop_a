 /*
represents the lifecycle of a readlock on a dpapi_bundle
this object is returned from a dpapi_bundle when readlocked
deleting this object releases the readlock on the dpapi_bundle
*/

#ifndef dpapi_bundle_readlock_h
#define dpapi_bundle_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_bundle;

    class dpapi_bundle_readlock : public dpshared_readlock
    {

    private:

        dpapi_bundle *p;

    protected:

        //dtor
        virtual ~dpapi_bundle_readlock( void );

    public:

        //ctor
        dpapi_bundle_readlock( dpapi_bundle *p, dpmutex_readlock *ml );

    };

}

#endif








