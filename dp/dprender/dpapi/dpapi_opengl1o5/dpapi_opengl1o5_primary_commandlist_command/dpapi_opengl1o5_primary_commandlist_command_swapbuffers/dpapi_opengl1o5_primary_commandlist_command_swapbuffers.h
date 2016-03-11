
/*

*/

#ifndef dpapi_opengl1o5_primary_commandlist_command_swapbuffers_h
#define dpapi_opengl1o5_primary_commandlist_command_swapbuffers_h

#include "../../../dpapi/dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_swapbuffers/dpapi_primary_commandlist_command_swapbuffers.h"
#include "../../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"

namespace dp
{

    class dpapi_opengl1o5_primary_commandlist_command_swapbuffers : public dpapi_primary_commandlist_command_swapbuffers
    {

    private:

        opengl1o5_lib_functions *gl;

    protected:

    public:

        //ctor
        dpapi_opengl1o5_primary_commandlist_command_swapbuffers( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_primary_commandlist_command_swapbuffers( void );
        //compile command
        virtual bool compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif













