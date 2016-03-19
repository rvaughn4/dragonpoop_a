
/*

*/

#include "dpvertexbuffer.h"

namespace dp
{

    //ctor
    dpvertexbuffer::dpvertexbuffer( void )
    {

    }

    //dtor
    dpvertexbuffer::~dpvertexbuffer( void )
    {

    }

    //override to set element size
    unsigned int dpvertexbuffer::_getElementSize( void )
    {
        return sizeof( dpvertex );
    }

    //write element
    bool dpvertexbuffer::write( dpvertex *i )
    {
        return this->dpvarbuffer::write( (char *)i, sizeof( dpvertex ) );
    }

    //read element
    bool dpvertexbuffer::read( dpvertex *i )
    {
        return this->dpvarbuffer::read( (char *)i, sizeof( dpvertex ) );
    }

    //write element at index
    bool dpvertexbuffer::write( dpvertex *i, unsigned int index )
    {
        return this->dpvarbuffer::write( (char *)i, sizeof( dpvertex ), index );
    }

    //read element at index
    bool dpvertexbuffer::read( dpvertex *i, unsigned int index )
    {
        return this->dpvarbuffer::read( (char *)i, sizeof( dpvertex ), index );
    }

};


