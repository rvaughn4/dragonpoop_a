
/*

*/

#ifndef dpapi_opengl1o5_factory_h
#define dpapi_opengl1o5_factory_h

#include "../../dpapi/dpapi/dpapi_factory.h"

namespace dp
{

    class dpapi_opengl1o5_factory : public dpapi_factory
    {

    private:

    protected:


    public:

        //ctor
        dpapi_opengl1o5_factory( void );
        //dtor
        virtual ~dpapi_opengl1o5_factory( void );
        //creates window
        virtual dpapi *makeApi( void );
        //clones factory
        virtual dpapi_factory *clone( void );

    };

}

#endif







