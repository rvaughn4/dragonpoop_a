
/*
handles safe deletion of shared object refs
*/

#include "dpshared_ref_kernel.h"
#include "dpshared_ref.h"

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
        this->unlink();
    }

    //returns true if linked
    bool dpshared_ref_kernel::isLinked( void )
    {
        bool r;
        this->s.lock();
        r = this->bLinked;
        this->s.unlock();
        return r;
    }

    //unlink
    void dpshared_ref_kernel::unlink( void )
    {
        this->s.lock();
        this->bLinked = 0;
        this->s.unlock();
    }

}



