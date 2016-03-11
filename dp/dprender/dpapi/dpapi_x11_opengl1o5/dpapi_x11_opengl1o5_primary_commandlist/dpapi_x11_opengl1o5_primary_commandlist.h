
/*

*/

#ifndef dpapi_x11_opengl1o5_primary_commandlist_h
#define dpapi_x11_opengl1o5_primary_commandlist_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5_primary_commandlist/dpapi_opengl1o5_primary_commandlist.h"
#include "../dpapi_x11_opengl1o5/dpapi_x11_opengl1o5_functions.h"

namespace dp
{

    class dpapi_x11_opengl1o5_primary_commandlist : public dpapi_opengl1o5_primary_commandlist
    {

    private:

        opengl1o5_x11_lib_functions *gl;

    protected:

        //generate swap buffers command
        virtual dpapi_primary_commandlist_command *genCommandSwapBuffers( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );

    public:

        //ctor
        dpapi_x11_opengl1o5_primary_commandlist( dpapi_context_writelock *ctxl, opengl1o5_x11_lib_functions *gl );
        //dtor
        virtual ~dpapi_x11_opengl1o5_primary_commandlist( void );

    };

}

#endif









