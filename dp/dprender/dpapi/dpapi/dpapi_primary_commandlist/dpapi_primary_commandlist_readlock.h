/*
represents the lifecycle of a readlock on a dpapi_primary_commandlist
this object is returned from a dpapi_primary_commandlist when readlocked
deleting this object releases the readlock on the dpapi_primary_commandlist
*/

#ifndef dpapi_primary_commandlist_readlock_h
#define dpapi_primary_commandlist_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_primary_commandlist;
    class dpmutex_readlock;
    class dpapi_primary_commandlist_ref;

    class dpapi_primary_commandlist_readlock : public dpshared_readlock
    {

        dpapi_primary_commandlist *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_primary_commandlist_readlock( void );

    public:

        //ctor
        dpapi_primary_commandlist_readlock( dpapi_primary_commandlist *p, dpmutex_readlock *ml );

    };

}

#endif









