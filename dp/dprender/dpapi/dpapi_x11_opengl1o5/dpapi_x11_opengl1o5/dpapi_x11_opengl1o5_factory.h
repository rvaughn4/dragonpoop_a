
/*

*/

#ifndef dpapi_x11_opengl1o5_factory_h
#define dpapi_x11_opengl1o5_factory_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5/dpapi_opengl1o5_factory.h"
#include <string>

namespace dp
{

    class dpapi_x11_opengl1o5_factory : public dpapi_opengl1o5_factory
    {

    private:

        std::string sname;
        unsigned int w, h;

    protected:


    public:

        //ctor
        dpapi_x11_opengl1o5_factory( unsigned int w, unsigned int h, const char *cname );
        //dtor
        virtual ~dpapi_x11_opengl1o5_factory( void );
        //creates window
        virtual dpapi *makeApi( void );
        //clones factory
        virtual dpapi_factory *clone( void );

    };

}

#endif








