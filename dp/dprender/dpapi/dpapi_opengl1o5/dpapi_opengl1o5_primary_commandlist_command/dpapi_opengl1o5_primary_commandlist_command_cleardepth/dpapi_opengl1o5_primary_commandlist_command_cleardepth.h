
/*

*/

#ifndef dpapi_opengl1o5_primary_commandlist_command_cleardepth_h
#define dpapi_opengl1o5_primary_commandlist_command_cleardepth_h

#include "../../../dpapi/dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_cleardepth/dpapi_primary_commandlist_command_cleardepth.h"
#include "../../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"

namespace dp
{

    class dpapi_opengl1o5_primary_commandlist_command_cleardepth : public dpapi_primary_commandlist_command_cleardepth
    {

    private:

        opengl1o5_lib_functions *gl;
        float d;

    protected:

    public:

        //ctor
        dpapi_opengl1o5_primary_commandlist_command_cleardepth( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl, float d, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_primary_commandlist_command_cleardepth( void );
        //compile command
        virtual bool compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif














