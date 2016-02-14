
/*
handles safe deletion of shared object refs
*/

#include "dpshared_ref_kernel.h"

namespace dp
{

    //ctor
    dpshared_ref_kernel::dpshared_ref_kernel( void )
    {
        this->bLinked = 1;
    }

    //dtor
    dpshared_ref_kernel::~dpshared_ref_kernel( void )
    {

    }

    //returns true if linked
    bool dpshared_ref_kernel::isLinked( void )
    {
        return this->bLinked;
    }

    //unlink
    void dpshared_ref_kernel::unlink( void )
    {
        this->bLinked = 0;
    }

}



