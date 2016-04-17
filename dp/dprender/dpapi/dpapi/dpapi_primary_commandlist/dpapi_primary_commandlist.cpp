
/*

*/

#include "dpapi_primary_commandlist.h"
#include "dpapi_primary_commandlist_ref.h"
#include "dpapi_primary_commandlist_readlock.h"
#include "dpapi_primary_commandlist_writelock.h"
#include "../dpapi_primary_commandlist_command/dpapi_primary_commandlist_command/dpapi_primary_commandlist_command.h"
#include "../dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_clearcolor/dpapi_primary_commandlist_command_clearcolor.h"
#include "../dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_cleardepth/dpapi_primary_commandlist_command_cleardepth.h"
#include "../dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_swapbuffers/dpapi_primary_commandlist_command_swapbuffers.h"
#include "../dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_commandlist/dpapi_primary_commandlist_command_commandlist.h"
#include "../dpapi_primary_commandlist_command/dpapi_primary_commandlist_command_viewport/dpapi_primary_commandlist_command_viewport.h"

namespace dp
{

    //ctor
    dpapi_primary_commandlist::dpapi_primary_commandlist( dpapi_context_writelock *awl ) : dpshared()
    {
        this->zeroCommands();
    }

    //dtor
    dpapi_primary_commandlist::~dpapi_primary_commandlist( void )
    {
        this->unlink();
        this->deleteCommands();
    }

    //generate readlock
    dpshared_readlock *dpapi_primary_commandlist::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_primary_commandlist_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_primary_commandlist::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_primary_commandlist_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_primary_commandlist::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_primary_commandlist_ref( this, k, t_sync );
    }

    //add command
    bool dpapi_primary_commandlist::addCommand( dpapi_primary_commandlist_command *nc )
    {
        if( this->last_cmd >= dpapi_primary_commandlist_MAX_commands )
            return 0;
        if( !nc )
            return 0;

        this->cmds[ this->last_cmd ] = nc;
        this->last_cmd++;
        return 1;
    }

    //zero command list
    void dpapi_primary_commandlist::zeroCommands( void )
    {
        this->last_cmd = 0;
    }

    //delete all commands
    void dpapi_primary_commandlist::deleteCommands( void )
    {
        unsigned int i;
        dpapi_primary_commandlist_command *c;

        for( i = 0; i < this->last_cmd; i++ )
        {
            c = this->cmds[ i ];
            if( !c )
                continue;
            delete c;
            this->cmds[ i ] = 0;
        }

        this->zeroCommands();
    }

    //compile all commands
    bool dpapi_primary_commandlist::compileCommands( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        unsigned int i;
        dpapi_primary_commandlist_command *c;

        for( i = 0; i < this->last_cmd; i++ )
        {
            c = this->cmds[ i ];
            if( !c )
                continue;

            if( !c->compile( l, ctxl ) )
                return 0;
        }

        return 1;
    }

    //execute all commands
    bool dpapi_primary_commandlist::executeCommands( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        unsigned int i;
        dpapi_primary_commandlist_command *c;

        for( i = 0; i < this->last_cmd; i++ )
        {
            c = this->cmds[ i ];
            if( !c )
                continue;

            if( !c->execute( l, ctxl ) )
                return 0;
        }

        return 1;
    }

    //generate clear color buffer command
    dpapi_primary_commandlist_command *dpapi_primary_commandlist::genCommandClearColor( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float r, float g, float b, float a )
    {
        return new dpapi_primary_commandlist_command_clearcolor( l, ctxl, r, g, b, a );
    }

    //generate clear depth buffer command
    dpapi_primary_commandlist_command *dpapi_primary_commandlist::genCommandClearDepth( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float d )
    {
        return new dpapi_primary_commandlist_command_cleardepth( l, ctxl, d );
    }

    //generate start renderpass command
    dpapi_primary_commandlist_command *dpapi_primary_commandlist::genCommandRenderpassStart( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_renderpass *rp )
    {
        return 0;
    }

    //generate end renderpass command
    dpapi_primary_commandlist_command *dpapi_primary_commandlist::genCommandRenderpassEnd( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        return 0;
    }

    //generate commandlist command
    dpapi_primary_commandlist_command *dpapi_primary_commandlist::genCommandCommandList( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_commandlist *cl )
    {
        return new dpapi_primary_commandlist_command_commandlist( l, ctxl, cl );
    }

    //generate swap buffers command
    dpapi_primary_commandlist_command *dpapi_primary_commandlist::genCommandSwapBuffers( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        return new dpapi_primary_commandlist_command_swapbuffers( l, ctxl );
    }

    //generate viewport command
    dpapi_primary_commandlist_command *dpapi_primary_commandlist::genCommandViewport( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float x, float y, float w, float h )
    {
        return new dpapi_primary_commandlist_command_viewport( l, ctxl, x, y, w, h );
    }

    //clear commandlist and make ready for new commands / record mode
    bool dpapi_primary_commandlist::clearAndRecord( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        this->deleteCommands();
        return 1;
    }

    //compile commands to make ready for execute
    bool dpapi_primary_commandlist::compile( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        return this->compileCommands( l, ctxl );
    }

    //execute commands
    bool dpapi_primary_commandlist::execute( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        return this->executeCommands( l, ctxl );
    }

    //add clear color buffer command
    bool dpapi_primary_commandlist::clearColor( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float r, float g, float b, float a )
    {
        dpapi_primary_commandlist_command *c;
        c = this->genCommandClearColor( l, ctxl, r, g, b, a );
        return this->addCommand( c );
    }

    //add clear depth buffer command
    bool dpapi_primary_commandlist::clearDepth( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float d )
    {
        dpapi_primary_commandlist_command *c;
        c = this->genCommandClearDepth( l, ctxl, d );
        return this->addCommand( c );
    }

    //add begin renderpass command
    bool dpapi_primary_commandlist::startRenderpass( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_renderpass *rp )
    {
        dpapi_primary_commandlist_command *c;
        c = this->genCommandRenderpassStart( l, ctxl, rp );
        return this->addCommand( c );
    }

    //add end renderpass command
    bool dpapi_primary_commandlist::endRenderpass( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        dpapi_primary_commandlist_command *c;
        c = this->genCommandRenderpassEnd( l, ctxl );
        return this->addCommand( c );
    }

    //add commandlist command
    bool dpapi_primary_commandlist::addCommandList( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, dpapi_commandlist *cl )
    {
        dpapi_primary_commandlist_command *c;
        c = this->genCommandCommandList( l, ctxl, cl );
        return this->addCommand( c );
    }

    //add swap buffers
    bool dpapi_primary_commandlist::swapBuffers( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        dpapi_primary_commandlist_command *c;
        c = this->genCommandSwapBuffers( l, ctxl );
        return this->addCommand( c );
    }

    //add viewport command
    bool dpapi_primary_commandlist::viewport( dpapi_primary_commandlist_writelock *l, dpapi_context_writelock *ctxl, float x, float y, float w, float h )
    {
        dpapi_primary_commandlist_command *c;
        c = this->genCommandViewport( l, ctxl, x, y, w, h );
        return this->addCommand( c );
    }

}









