
/*

*/

#include "dpapi_commandlist.h"
#include "dpapi_commandlist_ref.h"
#include "dpapi_commandlist_readlock.h"
#include "dpapi_commandlist_writelock.h"
#include "../dpapi_commandlist_command/dpapi_commandlist_command/dpapi_commandlist_command.h"
#include "../dpapi_commandlist_command/dpapi_commandlist_command_bundle/dpapi_commandlist_command_bundle.h"

namespace dp
{

    //ctor
    dpapi_commandlist::dpapi_commandlist( dpapi_context_writelock *awl ) : dpshared()
    {
        this->zeroCommands();
    }

    //dtor
    dpapi_commandlist::~dpapi_commandlist( void )
    {
        this->unlink();
        this->deleteCommands();
    }

    //generate readlock
    dpshared_readlock *dpapi_commandlist::genReadLock( dpmutex_readlock *ml )
    {
        return new dpapi_commandlist_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpapi_commandlist::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpapi_commandlist_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpapi_commandlist::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpapi_commandlist_ref( this, k, t_sync );
    }

    //add command
    bool dpapi_commandlist::addCommand( dpapi_commandlist_command *nc )
    {
        if( this->last_cmd >= dpapi_commandlist_MAX_commands )
            return 0;
        if( !nc )
            return 0;

        this->cmds[ this->last_cmd ] = nc;
        this->last_cmd++;
        return 1;
    }

    //zero command list
    void dpapi_commandlist::zeroCommands( void )
    {
        this->last_cmd = 0;
    }

    //delete all commands
    void dpapi_commandlist::deleteCommands( void )
    {
        unsigned int i;
        dpapi_commandlist_command *c;

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
    bool dpapi_commandlist::compileCommands( dpapi_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        unsigned int i;
        dpapi_commandlist_command *c;

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
    bool dpapi_commandlist::executeCommands( dpapi_commandlist_writelock *l, dpapi_context_writelock *ctxl )
    {
        unsigned int i;
        dpapi_commandlist_command *c;

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

    //clear and make commandlist ready to accept commands
    bool dpapi_commandlist::clearAndRecord( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl )
    {
        this->deleteCommands();
        return 1;
    }

    //compile list
    bool dpapi_commandlist::compile( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl )
    {
        return this->compileCommands( wl, ctx );
    }

    //execute list
    bool dpapi_commandlist::execute( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl )
    {
        return this->executeCommands( wl, ctx );
    }

    //override to generate bundle command
    dpapi_commandlist_command *dpapi_commandlist::genBundleCommand( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl, dpapi_bundle *bdle )
    {
        return new dpapi_commandlist_command_bundle( wl, ctx, bdle );
    }

    //add bundle to commandlist
    bool dpapi_commandlist::addBundle( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl, dpapi_bundle *bdle )
    {
        dpapi_commandlist_command *nc;

        nc = this->genBundleCommand( ctx, wl, bdle );
        if( !nc )
            return 0;

        if( this->addCommand( nc ) )
            return 1;

        delete nc;
        return 0;
    }

}








