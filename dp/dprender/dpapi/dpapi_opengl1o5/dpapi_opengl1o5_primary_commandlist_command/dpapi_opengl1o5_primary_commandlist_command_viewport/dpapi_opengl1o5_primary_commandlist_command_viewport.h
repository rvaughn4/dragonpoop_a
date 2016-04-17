
/*

*/

#ifndef dpapi_opengl1o5_primary_commandlist_command_viewport_h
#define dpapi_opengl1o5_primary_commandlist_command_viewport_h

#include "../../../dpapi/dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_viewport/dpapi_primary_commandlist_command_viewport.h"
#include "../../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"

namespace dp
{

    class dpapi_opengl1o5_primary_commandlist_command_viewport : public dpapi_primary_commandlist_command_viewport
    {

    private:

        opengl1o5_lib_functions *gl;
        float x, y, w, h;

    protected:

    public:

        //ctor
        dpapi_opengl1o5_primary_commandlist_command_viewport( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float x, float y, float w, float h, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_primary_commandlist_command_viewport( void );
        //compile command
        virtual bool compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif













