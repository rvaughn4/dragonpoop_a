
/*

*/

#ifndef dpapi_commandlist_h
#define dpapi_commandlist_h

#include "../../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dpapi_context_writelock;
    class dpapi_commandlist_writelock;
    class dpapi_commandlist_command;
    class dpapi_bundle;
    class dpmatrix;
    #define dpapi_commandlist_MAX_commands 4096

    class dpapi_commandlist : public dpshared
    {

    private:

        dpapi_commandlist_command *cmds[ dpapi_commandlist_MAX_commands ];
        unsigned int last_cmd;

        //add command
        bool addCommand( dpapi_commandlist_command *nc );
        //zero command list
        void zeroCommands( void );
        //delete all commands
        void deleteCommands( void );
        //compile all commands
        bool compileCommands( dpapi_commandlist_writelock *l, dpapi_context_writelock *ctxl );
        //execute all commands
        bool executeCommands( dpapi_commandlist_writelock *l, dpapi_context_writelock *ctxl );

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //clear and make commandlist ready to accept commands
        virtual bool clearAndRecord( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl );
        //compile list
        virtual bool compile( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl );
        //execute list
        virtual bool execute( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl );
        //override to generate bundle command
        virtual dpapi_commandlist_command *genBundleCommand( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl, dpmatrix *mx, dpapi_bundle *bdle, float opacity );
        //add bundle to commandlist
        virtual bool addBundle( dpapi_context_writelock *ctx, dpapi_commandlist_writelock *wl, dpmatrix *mx, dpapi_bundle *bdle, float opacity );

    public:

        //ctor
        dpapi_commandlist( dpapi_context_writelock *ctxl );
        //dtor
        virtual ~dpapi_commandlist( void );

        friend class dpapi_commandlist_writelock;
        friend class dpapi_commandlist_readlock;
    };

}

#endif







