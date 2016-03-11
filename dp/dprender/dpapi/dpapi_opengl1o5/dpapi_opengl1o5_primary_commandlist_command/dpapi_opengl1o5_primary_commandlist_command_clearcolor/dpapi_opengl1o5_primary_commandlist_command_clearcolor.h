
/*

*/

#ifndef dpapi_opengl1o5_primary_commandlist_command_clearcolor_h
#define dpapi_opengl1o5_primary_commandlist_command_clearcolor_h

#include "../../../dpapi/dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_clearcolor/dpapi_primary_commandlist_command_clearcolor.h"
#include "../../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"

namespace dp
{

    class dpapi_opengl1o5_primary_commandlist_command_clearcolor : public dpapi_primary_commandlist_command_clearcolor
    {

    private:

        opengl1o5_lib_functions *gl;
        float r, g, b, a;

    protected:

    public:

        //ctor
        dpapi_opengl1o5_primary_commandlist_command_clearcolor( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float r, float g, float b, float a, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_primary_commandlist_command_clearcolor( void );
        //compile command
        virtual bool compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif















