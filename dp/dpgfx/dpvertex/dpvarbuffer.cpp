
/*

*/

#include "dpvarbuffer.h"

namespace dp
{

    //ctor
    dpvarbuffer::dpvarbuffer( void ) : dpbuffer_wrapper()
    {
        this->sz_element = 0;
        this->setWrapped( &this->b );
    }

    //dtor
    dpvarbuffer::~dpvarbuffer( void )
    {

    }

    //override to set element size
    unsigned int dpvarbuffer::_getElementSize( void )
    {
        return 1;
    }

    //write bytes to buffer
    bool dpvarbuffer::write( char *b, unsigned int sz )
    {
        unsigned int szr;

        if( !this->sz_element )
            this->sz_element = this->_getElementSize();

        if( sz <= this->sz_element )
            szr = this->sz_element - sz;
        else
        {
            szr = 0;
            sz = this->sz_element;
        }

        if( !this->writeAlignedBytes( b, sz ) )
            return 0;

        while( szr > 0 )
        {
            if( !this->writeAlignedByte( 0 ) )
                return 0;
            szr--;
        }

        return 1;
    }

    //read bytes to buffer
    bool dpvarbuffer::read( char *b, unsigned int sz )
    {
        unsigned int szr;
        uint8_t d;

        if( !this->sz_element )
            this->sz_element = this->_getElementSize();

        if( sz <= this->sz_element )
            szr = this->sz_element - sz;
        else
        {
            szr = 0;
            sz = this->sz_element;
        }

        if( !this->readAlignedBytes( b, sz ) )
            return 0;

        while( szr > 0 )
        {
            if( !this->readAlignedByte( &d ) )
                return 0;
            szr--;
        }

        return 1;
    }

    //write bytes to buffer at index
    bool dpvarbuffer::write( char *b, unsigned int sz, unsigned int index )
    {
        if( !this->sz_element )
            this->sz_element = this->_getElementSize();

        index *= this->sz_element;
        this->setWriteByteCursor( index );

        return this->write( b, sz );
    }

    //read bytes from bufffer at index
    bool dpvarbuffer::read( char *b, unsigned int sz, unsigned int index )
    {
        if( !this->sz_element )
            this->sz_element = this->_getElementSize();

        index *= this->sz_element;
        this->setReadByteCursor( index );

        return this->read( b, sz );
    }

    //return count of elements
    unsigned int dpvarbuffer::getCount( void )
    {
        if( !this->sz_element )
            this->sz_element = this->_getElementSize();
        if( !this->sz_element )
            return 0;
        return this->getSize() / this->sz_element;
    }

};


