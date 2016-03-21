
/*

*/

#include "dpbuffer_static.h"

namespace dp
{

    //ctor
    dpbuffer_static::dpbuffer_static( char *b, unsigned int sz )
    {
        this->b = b;
        this->sz = sz;
        this->setWriteByteCursor( sz );
    }

    //dtor
    dpbuffer_static::~dpbuffer_static( void )
    {

    }

    //returns buffer
    char *dpbuffer_static::_getBuffer( void )
    {
        return this->b;
    }

    //returns size of buffer (override)
    unsigned int dpbuffer_static::_getSize( void )
    {
        return this->sz;
    }

    //auto resize buffer if necessary so that buffer extends to or past byte offset given (override)
    bool dpbuffer_static::_autoResize( unsigned int sz )
    {
        return sz < this->sz;
    }

};



