
/*

*/

#ifndef dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers_h
#define dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers_h

#include "../../../dpapi_opengl1o5/dpapi_opengl1o5_primary_commandlist_command/dpapi_opengl1o5_primary_commandlist_command_swapbuffers/dpapi_opengl1o5_primary_commandlist_command_swapbuffers.h"
#include "../../dpapi_x11_opengl1o5/dpapi_x11_opengl1o5_functions.h"

namespace dp
{

    class dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers : public dpapi_opengl1o5_primary_commandlist_command_swapbuffers
    {

    private:

        opengl1o5_x11_lib_functions *gl;

    protected:

    public:

        //ctor
        dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, opengl1o5_x11_lib_functions *gl );
        //dtor
        virtual ~dpapi_x11_opengl1o5_primary_commandlist_command_swapbuffers( void );
        //compile command
        virtual bool compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif













