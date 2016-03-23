
/*

*/

#include "dpindexbuffer.h"

namespace dp
{

    //ctor
    dpindexbuffer::dpindexbuffer( void )
    {

    }

    //dtor
    dpindexbuffer::~dpindexbuffer( void )
    {

    }

    //override to set element size
    unsigned int dpindexbuffer::_getElementSize( void )
    {
        return sizeof( dpindex );
    }

    //write element
    bool dpindexbuffer::write( dpindex *i )
    {
        return this->dpvarbuffer::write( (char *)i, sizeof( dpindex ) );
    }

    //read element
    bool dpindexbuffer::read( dpindex *i )
    {
        return this->dpvarbuffer::read( (char *)i, sizeof( dpindex ) );
    }

    //write element at index
    bool dpindexbuffer::write( dpindex *i, unsigned int index )
    {
        return this->dpvarbuffer::write( (char *)i, sizeof( dpindex ), index );
    }

    //read element at index
    bool dpindexbuffer::read( dpindex *i, unsigned int index )
    {
        return this->dpvarbuffer::read( (char *)i, sizeof( dpindex ), index );
    }

};

