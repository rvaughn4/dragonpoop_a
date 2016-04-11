
/*

*/

#include "dpapi_factory.h"
#include "dpapi.h"
#include "../../../dpwindow/dpwindow/dpwindow_factory.h"

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
        return new dpapi( new dpwindow_factory() );
    }

    //clones factory
    dpapi_factory *dpapi_factory::clone( void )
    {
        return new dpapi_factory();
    }

}







