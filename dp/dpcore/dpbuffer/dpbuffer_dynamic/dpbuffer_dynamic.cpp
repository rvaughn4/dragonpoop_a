
/*

*/

#include "dpbuffer_dynamic.h"

namespace dp
{

    //ctor
    dpbuffer_dynamic::dpbuffer_dynamic( void )
    {
        this->b.b = 0;
        this->b.sz = 0;
    }

    //dtor
    dpbuffer_dynamic::~dpbuffer_dynamic( void )
    {
        if( this->b.b )
            delete[] this->b.b;
    }

    //returns buffer
    char *dpbuffer_dynamic::_getBuffer( void )
    {
        return this->b.b;
    }

    //returns size of buffer (override)
    unsigned int dpbuffer_dynamic::_getSize( void )
    {
        return this->b.sz;
    }

    //auto resize buffer if necessary so that buffer extends to or past byte offset given (override)
    bool dpbuffer_dynamic::_autoResize( unsigned int sz )
    {
        dpbuffer_dynamic_buffer nb, ob;
        unsigned int nsz, i;

        if( this->b.b && this->b.sz > sz )
            return 1;
        ob = this->b;

        nsz = 8 + ob.sz * 2;
        if( sz > nsz )
            nsz = sz + 8;
        nb.sz = nsz;
        nb.b = new char[ nsz ];

        if( !nb.b )
            return 0;

        this->b = nb;
        if( !ob.b || !ob.sz )
            return 1;

        for( i = 0; i < ob.sz; i++ )
            nb.b[ i ] = ob.b[ i ];
        delete[] ob.b;

        return 1;
    }

};



