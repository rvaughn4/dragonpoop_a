
/*

*/

#ifndef dpwindow_x11_factory_h
#define dpwindow_x11_factory_h

#include "../dpwindow/dpwindow_factory.h"

#include <string>

namespace dp
{

    class dpwindow_x11_factory : public dpwindow_factory
    {

    private:

        unsigned int w, h;
        std::string sname;

    protected:


    public:

        //ctor
        dpwindow_x11_factory( unsigned int w, unsigned int h, const char *cname );
        //dtor
        virtual ~dpwindow_x11_factory( void );
        //creates window
        virtual dpwindow *makeWindow( void );

    };

}

#endif






