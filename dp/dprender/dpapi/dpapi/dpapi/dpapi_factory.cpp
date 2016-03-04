
/*

*/

#include "dpapi_factory.h"
#include "dpapi.h"
#include "../../../dpwindow/dpwindow/dpwindow_factory.h"
#include "../../../dpwindow/dpwindow_x11/dpwindow_x11_factory.h"

namespace dp
{

    //ctor
    dpapi_factory::dpapi_factory( void )
    {

    }

    //dtor
    dpapi_factory::~dpapi_factory( void )
    {

    }

    //creates window
    dpapi *dpapi_factory::makeApi( void )
    {
        return new dpapi( new dpwindow_x11_factory( 800, 600, "derp" ) );
    }

}







