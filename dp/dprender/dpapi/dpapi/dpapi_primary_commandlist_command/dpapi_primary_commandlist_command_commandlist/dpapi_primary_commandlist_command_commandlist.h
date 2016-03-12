
/*

*/

#ifndef dpapi_primary_commandlist_command_commandlist_h
#define dpapi_primary_commandlist_command_commandlist_h

#include "../dpapi_primary_commandlist_command/dpapi_primary_commandlist_command.h"
#include "../../../../../dpcore/dpshared/dpshared_guard.h"

namespace dp
{

    class dpapi_commandlist;
    class dpapi_commandlist_ref;

    class dpapi_primary_commandlist_command_commandlist : public dpapi_primary_commandlist_command
    {

    private:

        dpshared_guard gcl;
        dpapi_commandlist_ref *cl;

    protected:

    public:

        //ctor
        dpapi_primary_commandlist_command_commandlist( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, dpapi_commandlist *cl );
        //dtor
        virtual ~dpapi_primary_commandlist_command_commandlist( void );
        //compile command
        virtual bool compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif










