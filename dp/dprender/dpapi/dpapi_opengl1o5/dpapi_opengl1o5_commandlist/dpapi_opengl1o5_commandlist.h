
/*

*/

#ifndef dpapi_opengl1o5_commandlist_h
#define dpapi_opengl1o5_commandlist_h

#include "../../dpapi/dpapi_commandlist/dpapi_commandlist.h"
#include "../dpapi_opengl1o5/dpapi_opengl1o5_functions.h"

namespace dp
{

    class dpapi_opengl1o5_context_writelock;

    class dpapi_opengl1o5_commandlist : public dpapi_commandlist
    {

    private:

        opengl1o5_lib_functions *gl;

    protected:

    public:

        //ctor
        dpapi_opengl1o5_commandlist( dpapi_opengl1o5_context_writelock *ctxl, opengl1o5_lib_functions *gl );
        //dtor
        virtual ~dpapi_opengl1o5_commandlist( void );

    };

}

#endif








