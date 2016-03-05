
/*

*/

#ifndef dpapi_x11_opengl1o5_h
#define dpapi_x11_opengl1o5_h

#include "../../dpapi_opengl1o5/dpapi_opengl1o5/dpapi_opengl1o5.h"

namespace dp
{

    class dpapi_x11_opengl1o5 : public dpapi_opengl1o5
    {

    private:

    protected:

    public:

        //ctor
        dpapi_x11_opengl1o5( unsigned int w, unsigned int h, const char *cname );
        //dtor
        virtual ~dpapi_x11_opengl1o5( void );

    };

}

#endif






