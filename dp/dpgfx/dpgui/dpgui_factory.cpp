
/*
*/

#include "dpgui.h"
#include "dpgui_factory.h"

namespace dp
{

    //ctor
    dpgui_factory::dpgui_factory( void )
    {

    }

    //dtor
    dpgui_factory::~dpgui_factory( void )
    {

    }

    //generate gui
    dpgui *dpgui_factory::genGui( void )
    {
        return new dpgui( 0, 0, 100, 100, "[align center]hello" );
    }

}






