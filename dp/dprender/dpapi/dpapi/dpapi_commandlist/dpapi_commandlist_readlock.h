/*
represents the lifecycle of a readlock on a dpapi_commandlist
this object is returned from a dpapi_commandlist when readlocked
deleting this object releases the readlock on the dpapi_commandlist
*/

#ifndef dpapi_commandlist_readlock_h
#define dpapi_commandlist_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi_commandlist;
    class dpmutex_readlock;
    class dpapi_commandlist_ref;

    class dpapi_commandlist_readlock : public dpshared_readlock
    {

        dpapi_commandlist *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_commandlist_readlock( void );

    public:

        //ctor
        dpapi_commandlist_readlock( dpapi_commandlist *p, dpmutex_readlock *ml );

    };

}

#endif








