/*
represents the lifecycle of a readlock on a dpapi
this object is returned from a dpapi when readlocked
deleting this object releases the readlock on the dpapi
*/

#ifndef dpapi_readlock_h
#define dpapi_readlock_h

#include "../../../../dpcore/dpshared/dpshared_readlock.h"

namespace dp
{

    class dpapi;
    class dpmutex_readlock;
    class dpapi_ref;

    class dpapi_readlock : public dpshared_readlock
    {

        dpapi *p;

    private:

    protected:

        //dtor
        virtual ~dpapi_readlock( void );

    public:

        //ctor
        dpapi_readlock( dpapi *p, dpmutex_readlock *ml );
        //returns true if open
        bool isOpen( void );

    };

}

#endif






