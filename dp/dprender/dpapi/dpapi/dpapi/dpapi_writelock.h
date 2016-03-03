 /*
represents the lifecycle of a writelock on a dpapi
this object is returned from a dpapi when writelocked
deleting this object releases the writelock on the dpapi
*/

#ifndef dpapi_writelock_h
#define dpapi_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi;
    class dpmutex_writelock;
    class dpapi_ref;

    class dpapi_writelock : public dpshared_writelock
    {

    private:

        dpapi *p;

    protected:

        //dtor
        virtual ~dpapi_writelock( void );

    public:

        //ctor
        dpapi_writelock( dpapi *p, dpmutex_writelock *ml );
        //returns true if open
        bool isOpen( void );

    };

}

#endif







