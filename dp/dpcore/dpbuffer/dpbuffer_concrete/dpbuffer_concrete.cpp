
/*

*/

#include "dpbuffer_concrete.h"
#include "../dpbuffer_static/dpbuffer_static.h"

namespace dp
{

    //ctor
    dpbuffer_concrete::dpbuffer_concrete( void ) :dpbuffer()
    {
        this->read.byte_cursor = 0;
        this->read.bit_cursor = 0;
        this->write = this->read;
    }

    //dtor
    dpbuffer_concrete::~dpbuffer_concrete( void )
    {

    }

    //helper function
    unsigned int dpbuffer_concrete__getOffset( unsigned int byte_cursor, unsigned int bit_cursor )
    {
        unsigned int r;

        r = bit_cursor;
        r -= byte_cursor * 8;

        return r;
    }

    //return read byte cursor
    unsigned int dpbuffer_concrete::getReadByteCursor( void )
    {
        return this->read.byte_cursor;
    }

    //set read byte cursor
    void dpbuffer_concrete::setReadByteCursor( unsigned int c )
    {
        this->read.byte_cursor = c;
        this->read.bit_cursor = c * 8;
    }

    //return write byte cursor
    unsigned int dpbuffer_concrete::getWriteByteCursor( void )
    {
        return this->write.byte_cursor;
    }

    //set write byte cursor
    void dpbuffer_concrete::setWriteByteCursor( unsigned int c )
    {
        this->write.byte_cursor = c;
        this->write.bit_cursor = c * 8;
    }

    //return read bit cursor
    unsigned int dpbuffer_concrete::getReadBitCursor( void )
    {
        return this->read.bit_cursor;
    }

    //set read bit cursor
    void dpbuffer_concrete::setReadBitCursor( unsigned int c )
    {
        this->read.byte_cursor = c / 8;
        this->read.bit_cursor = c;
    }

    //return write bit cursor
    unsigned int dpbuffer_concrete::getWriteBitCursor( void )
    {
        return this->write.bit_cursor;
    }

    //set write bit cursor
    void dpbuffer_concrete::setWriteBitCursor( unsigned int c )
    {
        this->write.bit_cursor = c;
        this->write.byte_cursor = c / 8;
    }

    //return bit offset in current byte for read cursor
    unsigned int dpbuffer_concrete::getReadBitOffset( void )
    {
        return dpbuffer_concrete__getOffset( this->read.byte_cursor, this->read.bit_cursor );
    }

    //return bit offset in current byte for write cursor
    unsigned int dpbuffer_concrete::getWriteBitOffset( void )
    {
        return dpbuffer_concrete__getOffset( this->write.byte_cursor, this->write.bit_cursor );
    }

    //read bit, returns true if read
    bool dpbuffer_concrete::readBit( bool *b )
    {
        unsigned int c, o, sz, cb;
        unsigned char *buf, pdat;

        c = this->read.bit_cursor;
        cb = this->read.byte_cursor * 8;
        sz = this->_getSize() * 8;

        if( c >= sz || cb >= sz )
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
    bool dpbuffer_concrete::writeBit( bool b )
    {
        unsigned int c, o, rm, m, ns;
        unsigned char *buf, pdat, bdat;

        c = this->write.bit_cursor;

        ns = c + 1;
        ns = ns / 8;
        if( !this->_autoResize( ns + 1 ) )
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
    bool dpbuffer_concrete::readAlignedByte( uint8_t *b )
    {
        unsigned int c, o, sz;
        unsigned char *buf;

        c = this->read.byte_cursor;
        o = this->getReadBitOffset();
        sz = this->_getSize();
        if( o )
            c++;
        if( c >= sz )
            return 0;

        buf = (unsigned char *)this->_getBuffer();
        if( !buf )
            return 0;

        *b = buf[ c ];

        this->setReadByteCursor( c + 1 );
        return 1;
    }

    //write aligned byte, returns true if written
    bool dpbuffer_concrete::writeAlignedByte( uint8_t b )
    {
        unsigned int c, o;
        unsigned char *buf;

        c = this->write.byte_cursor;
        o = this->getWriteBitOffset();
        if( o )
            c++;

        if( !this->_autoResize( c + 1 ) )
            return 0;

        buf = (unsigned char *)this->_getBuffer();
        if( !buf )
            return 0;

        buf[ c ] = b;

        this->setWriteByteCursor( c + 1 );
        return 1;
    }

    //read aligned byte, returns true if read
    bool dpbuffer_concrete::readUnalignedByte( uint8_t *b )
    {
        return this->readUnalignedByte( b, 8 );
    }

    //write aligned byte, returns true if written
    bool dpbuffer_concrete::writeUnalignedByte( uint8_t b )
    {
        return this->writeUnalignedByte( b, 8 );
    }

    //read aligned byte, returns true if read
    bool dpbuffer_concrete::readUnalignedByte( uint8_t *b, unsigned int sz )
    {
        unsigned int i, r;
        bool tv;

        r = 0;
        for( i = 0; i < sz; i++ )
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
    bool dpbuffer_concrete::writeUnalignedByte( uint8_t b, unsigned int sz )
    {
        unsigned int i, r, v;

        r = b;
        for( i = 0; i < sz; i++ )
        {
            v = r >> i;
            v = v & 1;
            if( !this->writeBit( v != 0 ) )
                return 0;
        }

        return 1;
    }

    //read aligned bytes into buffer until all are read
    bool dpbuffer_concrete::readAlignedBytes( dpbuffer *b )
    {
        return this->readAlignedBytes( b, this->write.byte_cursor );
    }

    //read aligned bytes into buffer until cnt bytes are read
    bool dpbuffer_concrete::readAlignedBytes( dpbuffer *b, unsigned int cnt )
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
    bool dpbuffer_concrete::readAlignedBytes( char *b, unsigned int sz )
    {
        return this->readAlignedBytes( b, sz, sz );
    }

    //read aligned bytes into buffer until cnt bytes are read
    bool dpbuffer_concrete::readAlignedBytes( char *b, unsigned int sz, unsigned int cnt )
    {
        dpbuffer_static sb( b, sz );
        sb.setWriteByteCursor( 0 );
        return this->readAlignedBytes( &sb, cnt );
    }

    //write aligned bytes from buffer until all are written
    bool dpbuffer_concrete::writeAlignedBytes( dpbuffer *b )
    {
        return b->readAlignedBytes( this );
    }

    //write aligned bytes from buffer until cnt bytes are written
    bool dpbuffer_concrete::writeAlignedBytes( dpbuffer *b, unsigned int cnt )
    {
        return b->readAlignedBytes( this, cnt );
    }

    //write aligned bytes from buffer until all are written
    bool dpbuffer_concrete::writeAlignedBytes( char *b, unsigned int sz )
    {
        dpbuffer_static sb( b, sz );
        return this->writeAlignedBytes( &sb );
    }

    //write aligned bytes from buffer until cnt bytes are written
    bool dpbuffer_concrete::writeAlignedBytes( char *b, unsigned int sz, unsigned int cnt )
    {
        dpbuffer_static sb( b, sz );
        return this->writeAlignedBytes( &sb, cnt );
    }

    //return size in bytes
    unsigned int dpbuffer_concrete::getSize( void )
    {
        unsigned int s, r;

        r = this->write.byte_cursor;
        s = this->_getSize();
        if( r > s )
            r = s;

        return r;
    }

    //return size in bits
    unsigned int dpbuffer_concrete::getSizeBits( void )
    {
        unsigned int s, r;

        r = this->write.bit_cursor;
        s = this->_getSize() * 8;
        if( r > s )
            r = s;

        return r;
    }

    //copy buffer into this buffer
    void dpbuffer_concrete::copy( dpbuffer *b )
    {
        unsigned int wc, rc, i;
        uint8_t v;
        bool bv;

        wc = b->getWriteBitCursor();
        rc = b->getReadBitCursor();

        b->setReadByteCursor( 0 );
        this->setWriteByteCursor( 0 );

        for( i = 0; i < wc; i+=8 )
        {
            b->readAlignedByte( &v );
            this->writeAlignedByte( v );
        }
        for( ; i < wc; i++ )
        {
            b->readBit( &bv );
            this->writeBit( bv );
        }

        b->setWriteBitCursor( wc );
        this->setWriteBitCursor( wc );
        b->setReadBitCursor( rc );
        this->setReadBitCursor( rc );
    }

    //get pointer to buffer
    char *dpbuffer_concrete::getBuffer( void )
    {
        return this->_getBuffer();
    }

    //get section at offset with size
    bool dpbuffer_concrete::getSection( dpbuffer_static *bs, unsigned int offset, unsigned int sz )
    {
        unsigned int tsz, twc;
        char *b;

        tsz = this->_getSize();
        twc = this->write.byte_cursor;
        b = this->_getBuffer();

        if( twc < tsz )
            tsz = twc;
        if( offset + sz > tsz )
            return 0;
        if( !b )
            return 0;

        bs->setBuffer( &b[ offset ], sz );
        return 1;
    }

};



