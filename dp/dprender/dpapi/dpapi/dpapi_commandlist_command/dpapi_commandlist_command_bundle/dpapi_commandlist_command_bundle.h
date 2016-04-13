
/*

*/

#ifndef dpapi_commandlist_command_bundle_h
#define dpapi_commandlist_command_bundle_h

#include "../dpapi_commandlist_command/dpapi_commandlist_command.h"

namespace dp
{

    class dpapi_bundle;
    class dpmatrix;

    class dpapi_commandlist_command_bundle : public dpapi_commandlist_command
    {

    private:

        dpapi_bundle *bdle;

    protected:

        //return internal bundle
        dpapi_bundle *getBundle( void );

    public:

        //ctor
        dpapi_commandlist_command_bundle( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl, dpmatrix *mx, dpapi_bundle *bdle );
        //dtor
        virtual ~dpapi_commandlist_command_bundle( void );
        //compile command
        virtual bool compile( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif











