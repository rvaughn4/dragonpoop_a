 /*
represents the lifecycle of a writelock on a dpapi_commandlist
this object is returned from a dpapi_commandlist when writelocked
deleting this object releases the writelock on the dpapi_commandlist
*/

#ifndef dpapi_commandlist_writelock_h
#define dpapi_commandlist_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_commandlist;

    class dpapi_commandlist_writelock : public dpshared_writelock
    {

    private:

        dpapi_commandlist *p;

    protected:

        //dtor
        virtual ~dpapi_commandlist_writelock( void );

    public:

        //ctor
        dpapi_commandlist_writelock( dpapi_commandlist *p, dpmutex_writelock *ml );

    };

}

#endif









