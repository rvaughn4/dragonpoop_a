
/*

*/

#include "dpbitmap.h"
#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"

namespace dp
{

    //ctor
    dpbitmap::dpbitmap( void ) : dpbuffer_wrapper()
    {
        this->setWrapped( &this->int_b );
    }

    //ctor
    dpbitmap::dpbitmap( dpbuffer *b ) : dpbuffer_wrapper( b )
    {

    }

    //dtor
    dpbitmap::~dpbitmap( void )
    {

    }

};



