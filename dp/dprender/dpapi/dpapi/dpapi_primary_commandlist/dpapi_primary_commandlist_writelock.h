 /*
represents the lifecycle of a writelock on a dpapi_primary_commandlist
this object is returned from a dpapi_primary_commandlist when writelocked
deleting this object releases the writelock on the dpapi_primary_commandlist
*/

#ifndef dpapi_primary_commandlist_writelock_h
#define dpapi_primary_commandlist_writelock_h

#include "../../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dpapi_primary_commandlist;
    class dpapi_context_writelock;
    class dpapi_renderpass;
    class dpapi_commandlist;

    class dpapi_primary_commandlist_writelock : public dpshared_writelock
    {

    private:

        dpapi_primary_commandlist *p;

    protected:

        //dtor
        virtual ~dpapi_primary_commandlist_writelock( void );

    public:

        //ctor
        dpapi_primary_commandlist_writelock( dpapi_primary_commandlist *p, dpmutex_writelock *ml );
        //clear commandlist and make ready for new commands / record mode
        bool clearAndRecord( dpapi_context_writelock *ctxl );
        //compile commands to make ready for execute
        bool compile( dpapi_context_writelock *ctxl );
        //execute commands
        bool execute( dpapi_context_writelock *ctxl );
        //add clear color buffer command
        bool clearColor( dpapi_context_writelock *ctxl, float r, float g, float b, float a );
        //add clear depth buffer command
        bool clearDepth( dpapi_context_writelock *ctxl, float d );
        //add begin renderpass command
        bool startRenderpass( dpapi_context_writelock *ctxl, dpapi_renderpass *rp );
        //add end renderpass command
        bool endRenderpass( dpapi_context_writelock *ctxl );
        //add commandlist command
        bool addCommandList( dpapi_context_writelock *ctxl, dpapi_commandlist *cl );
        //add swap buffers
        bool swapBuffers( dpapi_context_writelock *ctxl );
        //add viewport command
        bool viewport( dpapi_context_writelock *ctxl, float x, float y, float w, float h );

    };

}

#endif










