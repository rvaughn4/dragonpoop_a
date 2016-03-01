
/*

*/

#include "dpwindow_x11_factory.h"
#include "dpwindow_x11.h"

namespace dp
{

    //ctor
    dpwindow_x11_factory::dpwindow_x11_factory( unsigned int w, unsigned int h, const char *cname )
    {
        this->sname.assign( cname );
        this->w = w;
        this->h = h;
    }

    //dtor
    dpwindow_x11_factory::~dpwindow_x11_factory( void )
    {

    }

    //creates window
    dpwindow *dpwindow_x11_factory::makeWindow( void )
    {
        return new dpwindow_x11( this->w, this->h, this->sname.c_str() );
    }

}







