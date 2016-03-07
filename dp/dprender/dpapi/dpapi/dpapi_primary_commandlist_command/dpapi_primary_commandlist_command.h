
/*

*/

#ifndef dpapi_primary_commandlist_command_h
#define dpapi_primary_commandlist_command_h

namespace dp
{

    class dpapi_context_writelock;
    class dpapi_primary_commandlist_writelock;

    class dpapi_primary_commandlist_command
    {

    private:

    protected:

    public:

        //ctor
        dpapi_primary_commandlist_command( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //dtor
        virtual ~dpapi_primary_commandlist_command( void );
        //compile command
        virtual bool compile( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_primary_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif









