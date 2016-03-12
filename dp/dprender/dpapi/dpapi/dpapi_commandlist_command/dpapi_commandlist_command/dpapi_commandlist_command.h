
/*

*/

#ifndef dpapi_commandlist_command_h
#define dpapi_commandlist_command_h

namespace dp
{

    class dpapi_context_writelock;
    class dpapi_commandlist_writelock;

    class dpapi_commandlist_command
    {

    private:

    protected:

    public:

        //ctor
        dpapi_commandlist_command( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //dtor
        virtual ~dpapi_commandlist_command( void );
        //compile command
        virtual bool compile( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl );
        //execute command
        virtual bool execute( dpapi_commandlist_writelock *p, dpapi_context_writelock *ctxl );

    };

}

#endif










