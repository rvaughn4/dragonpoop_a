
/*

*/

#ifndef dpapi_primary_commandlist_h
#define dpapi_primary_commandlist_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpapi_context_writelock;
    class dpapi_primary_commandlist_writelock;
    class dpapi_primary_commandlist_command;
    class dpapi_renderpass;
    class dpapi_commandlist;

    #define dpapi_primary_commandlist_MAX_commands 64

    class dpapi_primary_commandlist : public dpshared
    {

    private:

        dpapi_primary_commandlist_command *cmds[ dpapi_primary_commandlist_MAX_commands ];
        unsigned int last_cmd;

        //add command
        bool addCommand( dpapi_primary_commandlist_command *nc );
        //zero command list
        void zeroCommands( void );
        //delete all commands
        void deleteCommands( void );
        //compile all commands
        bool compileCommands( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );
        //execute all commands
        bool executeCommands( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

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
        //generate viewport command
        virtual dpapi_primary_commandlist_command *genCommandViewport( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float x, float y, float w, float h );

        //clear commandlist and make ready for new commands / record mode
        virtual bool clearAndRecord( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );
        //compile commands to make ready for execute
        virtual bool compile( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );
        //execute commands
        virtual bool execute( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );

        //add clear color buffer command
        virtual bool clearColor( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float r, float g, float b, float a );
        //add clear depth buffer command
        virtual bool clearDepth( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float d );
        //add begin renderpass command
        virtual bool startRenderpass( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_renderpass *rp );
        //add end renderpass command
        virtual bool endRenderpass( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );
        //add commandlist command
        virtual bool addCommandList( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_commandlist *cl );
        //add swap buffers
        virtual bool swapBuffers( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl );
        //add viewport command
        virtual bool viewport( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float x, float y, float w, float h );

    public:

        //ctor
        dpapi_primary_commandlist( dpapi_context_writelock *ctxl );
        //dtor
        virtual ~dpapi_primary_commandlist( void );

        friend class dpapi_primary_commandlist_writelock;
        friend class dpapi_primary_commandlist_readlock;
    };

}

#endif








