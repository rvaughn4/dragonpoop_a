
/*

*/

#include "dpwindow_factory.h"
#include "dpwindow.h"

namespace dp
{

    //ctor
    dpwindow_factory::dpwindow_factory( void )
    {

    }

    //dtor
    dpwindow_factory::~dpwindow_factory( void )
    {

    }

    //creates window
    dpwindow *dpwindow_factory::makeWindow( void )
    {
        return new dpwindow();
    }

}






