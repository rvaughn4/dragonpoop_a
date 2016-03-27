
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
    dpbitmap::dpbitmap( dpbuffer *b ) : dpbuffer_wrapper()
    {
        this->int_b.copy( b );
        this->setWrapped( &this->int_b );
    }

    //dtor
    dpbitmap::~dpbitmap( void )
    {

    }

    //load buffer from buffer
    bool dpbitmap::load( dpbuffer *b )
    {
        return this->dpbuffer_wrapper::load( b );
    }

    //load buffer from file
    bool dpbitmap::load( const char *fname )
    {
        return this->dpbuffer_wrapper::load( fname );
    }

    //save buffer to file
    bool dpbitmap::save( const char *fname )
    {
        return this->dpbuffer_wrapper::save( fname );
    }

    //save buffer to buffer
    bool dpbitmap::save( dpbuffer *b )
    {
        return this->dpbuffer_wrapper::save( b );
    }

};



