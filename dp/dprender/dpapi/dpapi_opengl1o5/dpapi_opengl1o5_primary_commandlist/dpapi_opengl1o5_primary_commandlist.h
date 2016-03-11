
/*

*/

#ifndef dpapi_opengl1o5_primary_commandlist_h
#define dpapi_opengl1o5_primary_commandlist_h

#include "../../dpapi/dpapi_primary_commandlist/dpapi_primary_commandlist.h"
#include "../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"

namespace dp
{

    class dpapi_opengl1o5_primary_commandlist : public dpapi_primary_commandlist
    {

    private:

        opengl1o5_lib_functions *gl;

    protected:

        //generate clear color buffer command
        virtual dpapi_primary_commandlist_command *genCommandClearColor( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float r, float g, float b, float a );
        //generate clear depth buffer command
        virtual dpapi_primary_commandlist_command *genCommandClearDepth( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float d );
        //generate start renderpass command
        virtual dpapi_primary_commandlist_command *genCommandRenderpassStart( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_renderpass *rp );
        //generate end renderpass command
        virtual dpapi_primary_commandlist_command *genCommandRenderpassEnd( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );
        //generate commandlist command
        virtual dpapi_primary_commandlist_command *genCommandCommandList( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_commandlist *cl );
        //generate swap buffers command
        virtual dpapi_primary_commandlist_command *genCommandSwapBuffers( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );

    public:

        //ctor
        dpapi_opengl1o5_primary_commandlist( dpapi_context_writelock *ctxl, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_primary_commandlist( void );

    };

}

#endif









