
/*

*/

#include "dpbuffer.h"
#include "../dpbuffer_static/dpbuffer_static.h"

namespace dp
{

    //ctor
    dpbuffer::dpbuffer( void )
    {
        this->read.byte_cursor = 0;
        this->read.bit_cursor = 0;
        this->write = this->read;
    }

    //dtor
    dpbuffer::~dpbuffer( void )
    {

    }

    //helper function
    unsigned int dpbuffer__getOffset( unsigned int byte_cursor, unsigned int bit_cursor )
    {
        unsigned int r;

        r = byte_cursor * 8;
        r -= bit_cursor;

        return r;
    }

    //return read byte cursor
    unsigned int dpbuffer::getReadByteCursor( void )
    {
        return this->read.byte_cursor;
    }

    //set read byte cursor
    void dpbuffer::setReadByteCursor( unsigned int c )
    {
        this->read.byte_cursor = c;
        this->read.bit_cursor = c * 8;
    }

    //return write byte cursor
    unsigned int dpbuffer::getWriteByteCursor( void )
    {
        return this->write.byte_cursor;
    }

    //set write byte cursor
    void dpbuffer::setWriteByteCursor( unsigned int c )
    {
        this->write.byte_cursor = c;
        this->write.bit_cursor = c * 8;
    }

    //return read bit cursor
    unsigned int dpbuffer::getReadBitCursor( void )
    {
        return this->read.bit_cursor;
    }

    //set read bit cursor
    void dpbuffer::setReadBitCursor( unsigned int c )
    {
        this->read.byte_cursor = c;
        this->read.bit_cursor = c / 8;
    }

    //return write bit cursor
    unsigned int dpbuffer::getWriteBitCursor( void )
    {
        return this->write.bit_cursor;
    }

    //set write bit cursor
    void dpbuffer::setWriteBitCursor( unsigned int c )
    {
        this->write.byte_cursor = c;
        this->write.bit_cursor = c / 8;
    }

    //return bit offset in current byte for read cursor
    unsigned int dpbuffer::getReadBitOffset( void )
    {
        return dpbuffer__getOffset( this->read.byte_cursor, this->read.bit_cursor );
    }

    //return bit offset in current byte for write cursor
    unsigned int dpbuffer::getWriteBitOffset( void )
    {
        return dpbuffer__getOffset( this->write.byte_cursor, this->write.bit_cursor );
    }

    //read bit, returns true if read
    bool dpbuffer::readBit( bool *b )
    {
        unsigned int c, o;
        unsigned char *buf, pdat;

        c = this->read.bit_cursor;

        if( !this->_autoResize( c / 8 ) )
            return 0;

        o = this->getReadBitOffset();

        buf = (unsigned char *)this->_getBuffer();
        if( !buf )
            return 0;

        pdat = buf[ this->read.byte_cursor ];
        pdat = pdat >> o;
        pdat = pdat & 1;
        *b = pdat != 0;

        this->setReadBitCursor( c + 1 );
        return 1;
    }

    //write bit, returns true if written
    bool dpbuffer::writeBit( bool b )
    {
        unsigned int c, o, rm, m;
        unsigned char *buf, pdat, bdat;

        c = this->write.bit_cursor;

        if( !this->_autoResize( c / 8 ) )
            return 0;

        o = this->getWriteBitOffset();

        buf = (unsigned char *)this->_getBuffer();
        if( !buf )
            return 0;

        m = 1 << o;
        rm = ~m;

        pdat = buf[ this->write.byte_cursor ];
        pdat = pdat & rm;
        bdat = 0;
        if( b )
            bdat = m;
        pdat |= bdat;
        buf[ this->write.byte_cursor ] = pdat;

        this->setWriteBitCursor( c + 1 );
        return 1;
    }

    //read aligned byte, returns true if read
    bool dpbuffer::readAlignedByte( uint8_t *b )
    {
        unsigned int c, o;
        unsigned char *buf;

        c = this->read.byte_cursor;
        o = this->getReadBitOffset();
        if( o )
            c++;

        if( !this->_autoResize( c ) )
            return 0;

        buf = (unsigned char *)this->_getBuffer();
        if( !buf )
            return 0;

        *b = buf[ c ];

        this->setReadByteCursor( c + 1 );
        return 1;
    }

    //write aligned byte, returns true if written
    bool dpbuffer::writeAlignedByte( uint8_t b )
    {
        unsigned int c, o;
        unsigned char *buf;

        c = this->write.byte_cursor;
        o = this->getWriteBitOffset();
        if( o )
            c++;

        if( !this->_autoResize( c ) )
            return 0;

        buf = (unsigned char *)this->_getBuffer();
        if( !buf )
            return 0;

        buf[ c ] = b;

        this->setWriteByteCursor( c + 1 );
        return 1;
    }

    //read aligned byte, returns true if read
    bool dpbuffer::readUnalignedByte( uint8_t *b )
    {
        unsigned int i, r;
        bool tv;

        r = 0;
        for( i = 0; i < 8; i++ )
        {
            if( !this->readBit( &tv ) )
                return 0;
            if( !tv )
                continue;
            r |= 1 << i;
        }

        *b = r;
        return 1;
    }

    //write aligned byte, returns true if written
    bool dpbuffer::writeUnalignedByte( uint8_t b )
    {
        unsigned int i, r, v;

        r = b;
        for( i = 0; i < 8; i++ )
        {
            v = r >> i;
            v = v & 1;
            if( !this->writeBit( v != 0 ) )
                return 0;
        }

        return 1;
    }

    //read aligned bytes into buffer until all are read
    bool dpbuffer::readAlignedBytes( dpbuffer *b )
    {
        return this->readAlignedBytes( b, this->write.byte_cursor );
    }

    //read aligned bytes into buffer until cnt bytes are read
    bool dpbuffer::readAlignedBytes( dpbuffer *b, unsigned int cnt )
    {
        uint8_t v;
        unsigned int i;

        for( i = 0; i < cnt; i++ )
        {
            if( !this->readAlignedByte( &v ) )
                return 0;
            if( !b->writeAlignedByte( v ) )
                return 0;
        }

        return 1;
    }

    //read aligned bytes into buffer until all are read
    bool dpbuffer::readAlignedBytes( char *b, unsigned int sz )
    {
        return this->readAlignedBytes( b, sz, this->write.byte_cursor );
    }

    //read aligned bytes into buffer until cnt bytes are read
    bool dpbuffer::readAlignedBytes( char *b, unsigned int sz, unsigned int cnt )
    {
        dpbuffer_static sb( b, sz );
        return this->readAlignedBytes( &sb, cnt );
    }

    //write aligned bytes from buffer until all are written
    bool dpbuffer::writeAlignedBytes( dpbuffer *b )
    {
        return b->readAlignedBytes( this );
    }

    //write aligned bytes from buffer until cnt bytes are written
    bool dpbuffer::writeAlignedBytes( dpbuffer *b, unsigned int cnt )
    {
        return b->readAlignedBytes( this, cnt );
    }

    //write aligned bytes from buffer until all are written
    bool dpbuffer::writeAlignedBytes( char *b, unsigned int sz )
    {
        dpbuffer_static sb( b, sz );
        return this->writeAlignedBytes( &sb );
    }

    //write aligned bytes from buffer until cnt bytes are written
    bool dpbuffer::writeAlignedBytes( char *b, unsigned int sz, unsigned int cnt )
    {
        dpbuffer_static sb( b, sz );
        return this->writeAlignedBytes( &sb, cnt );
    }

};


