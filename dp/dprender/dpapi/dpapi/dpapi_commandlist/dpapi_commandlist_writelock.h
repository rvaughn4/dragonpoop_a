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
    class dpapi_context_writelock;
    class dpapi_bundle;
    class dpmatrix;

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
        //clear and make commandlist ready to accept commands
        bool clearAndRecord( dpapi_context_writelock *ctx );
        //compile list
        bool compile( dpapi_context_writelock *ctx );
        //execute list
        bool execute( dpapi_context_writelock *ctx );
        //add bundle to commandlist
        bool addBundle( dpapi_context_writelock *ctx, dpmatrix *mx, dpapi_bundle *bdle, float opacity );

    };

}

#endif









