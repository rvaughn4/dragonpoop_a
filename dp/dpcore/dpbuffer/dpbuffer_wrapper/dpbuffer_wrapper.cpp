
/*

*/

#include "dpbuffer_wrapper.h"

namespace dp
{

    //ctor
    dpbuffer_wrapper::dpbuffer_wrapper( dpbuffer *b )
    {
        this->b = b;
    }

    //ctor
    dpbuffer_wrapper::dpbuffer_wrapper( void )
    {
        this->b = 0;
    }

    //dtor
    dpbuffer_wrapper::~dpbuffer_wrapper( void )
    {

    }

    //set wrapped
    void dpbuffer_wrapper::setWrapped( dpbuffer *b )
    {
        this->b = b;
    }

    //returns buffer
    char *dpbuffer_wrapper::_getBuffer( void )
    {
        return 0;
    }

    //returns size of buffer (override)
    unsigned int dpbuffer_wrapper::_getSize( void )
    {
        return 0;
    }

    //auto resize buffer if necessary so that buffer extends to or past byte offset given (override)
    bool dpbuffer_wrapper::_autoResize( unsigned int sz )
    {
        return 0;
    }

    //return read byte cursor
    unsigned int dpbuffer_wrapper::getReadByteCursor( void )
    {
        return this->b->getReadByteCursor();
    }

    //set read byte cursor
    void dpbuffer_wrapper::setReadByteCursor( unsigned int c )
    {
        this->b->setReadByteCursor( c );
    }

    //return write byte cursor
    unsigned int dpbuffer_wrapper::getWriteByteCursor( void )
    {
        return this->b->getWriteByteCursor();
    }

    //set write byte cursor
    void dpbuffer_wrapper::setWriteByteCursor( unsigned int c )
    {
        return this->b->setWriteByteCursor( c );
    }

    //return read bit cursor
    unsigned int dpbuffer_wrapper::getReadBitCursor( void )
    {
        return this->b->getReadBitCursor();
    }

    //set read bit cursor
    void dpbuffer_wrapper::setReadBitCursor( unsigned int c )
    {
        this->b->setReadBitCursor( c );
    }

    //return write bit cursor
    unsigned int dpbuffer_wrapper::getWriteBitCursor( void )
    {
        return this->b->getWriteBitCursor();
    }

    //set write bit cursor
    void dpbuffer_wrapper::setWriteBitCursor( unsigned int c )
    {
        this->b->setWriteBitCursor( c );
    }

    //return bit offset in current byte for read cursor
    unsigned int dpbuffer_wrapper::getReadBitOffset( void )
    {
        return this->b->getReadBitOffset();
    }

    //return bit offset in current byte for write cursor
    unsigned int dpbuffer_wrapper::getWriteBitOffset( void )
    {
        return this->b->getWriteBitOffset();
    }

    //read bit, returns true if read
    bool dpbuffer_wrapper::readBit( bool *b )
    {
        return this->b->readBit( b );
    }

    //write bit, returns true if written
    bool dpbuffer_wrapper::writeBit( bool b )
    {
        return this->b->writeBit( b );
    }

    //read aligned byte, returns true if read
    bool dpbuffer_wrapper::readAlignedByte( uint8_t *b )
    {
        return this->b->readAlignedByte( b );
    }

    //write aligned byte, returns true if written
    bool dpbuffer_wrapper::writeAlignedByte( uint8_t b )
    {
        return this->b->writeAlignedByte( b );
    }

    //read aligned byte, returns true if read
    bool dpbuffer_wrapper::readUnalignedByte( uint8_t *b )
    {
        return this->b->readUnalignedByte( b );
    }

    //write aligned byte, returns true if written
    bool dpbuffer_wrapper::writeUnalignedByte( uint8_t b )
    {
        return this->b->writeUnalignedByte( b );
    }

    //read aligned bytes into buffer until all are read
    bool dpbuffer_wrapper::readAlignedBytes( dpbuffer *b )
    {
        return this->b->readAlignedBytes( b );
    }

    //read aligned bytes into buffer until cnt bytes are read
    bool dpbuffer_wrapper::readAlignedBytes( dpbuffer *b, unsigned int cnt )
    {
        return this->b->readAlignedBytes( b, cnt );
    }

    //read aligned bytes into buffer until all are read
    bool dpbuffer_wrapper::readAlignedBytes( char *b, unsigned int sz )
    {
        return this->b->readAlignedBytes( b, sz );
    }

    //read aligned bytes into buffer until cnt bytes are read
    bool dpbuffer_wrapper::readAlignedBytes( char *b, unsigned int sz, unsigned int cnt )
    {
        return this->b->readAlignedBytes( b, sz, cnt );
    }

    //write aligned bytes from buffer until all are written
    bool dpbuffer_wrapper::writeAlignedBytes( dpbuffer *b )
    {
        return this->b->writeAlignedBytes( b );
    }

    //write aligned bytes from buffer until cnt bytes are written
    bool dpbuffer_wrapper::writeAlignedBytes( dpbuffer *b, unsigned int cnt )
    {
        return this->b->writeAlignedBytes( b, cnt );
    }

    //write aligned bytes from buffer until all are written
    bool dpbuffer_wrapper::writeAlignedBytes( char *b, unsigned int sz )
    {
        return this->b->writeAlignedBytes( b, sz );
    }

    //write aligned bytes from buffer until cnt bytes are written
    bool dpbuffer_wrapper::writeAlignedBytes( char *b, unsigned int sz, unsigned int cnt )
    {
        return this->b->writeAlignedBytes( b, sz, cnt );
    }

};


