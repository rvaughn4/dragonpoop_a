
/*

*/

#ifndef dpapi_primary_commandlist_command_viewport_h
#define dpapi_primary_commandlist_command_viewport_h

#include "../dpapi_primary_commandlist_command/dpapi_primary_commandlist_command.h"

namespace dp
{

    class dpapi_primary_commandlist_command_viewport : public dpapi_primary_commandlist_command
    {

    private:

    protected:

    public:

        //ctor
        dpapi_primary_commandlist_command_viewport( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float x, float y, float w, float h );
        //dtor
        virtual ~dpapi_primary_commandlist_command_viewport( void );
        //compile command
        virtual bool compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif












