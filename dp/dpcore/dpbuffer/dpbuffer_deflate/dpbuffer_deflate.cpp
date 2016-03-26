
/*

*/

#include "dpbuffer_deflate.h"
#include "../dpbuffer/dpbuffer.h"

namespace dp
{

    //ctor
    dpbuffer_deflate::dpbuffer_deflate( void )
    {

    }

    //dtor
    dpbuffer_deflate::~dpbuffer_deflate( void )
    {

    }

    //compress source buffer and output into dest buffer
    bool dpbuffer_deflate::compress( dpbuffer *src, dpbuffer *dest )
    {
        bool r = 0;

        while( this->writeSection( src, dest, 1024 ) )
            r = 1;

        return r;
    }

    //decompress source buffer and output into dest buffer
    bool dpbuffer_deflate::decompress( dpbuffer *src, dpbuffer *dest )
    {
        bool r = 0;

        while( this->readSection( src, dest ) )
            r = 1;

        return r;
    }

    //read next section
    bool dpbuffer_deflate::readSection( dpbuffer *src, dpbuffer *dest )
    {
        uint8_t cd;
        unsigned int rc, sz;

        rc = src->getReadByteCursor();
        sz = src->getWriteByteCursor();
        if( rc >= sz )
            return 0;

        cd = 0;
        if( !src->readUnalignedByte( &cd, 3 ) )
            return 0;

        switch( cd )
        {
            case dpbuffer_deflate_no_compress:
                return this->readUncompressed( src, dest );
            case dpbuffer_deflate_static_huffman:
                return 0;
            case dpbuffer_deflate_dynamic_huffman:
                return 0;
        }

        return 0;
    }

    //write next section
    bool dpbuffer_deflate::writeSection( dpbuffer *src, dpbuffer *dest, unsigned int len )
    {
        uint8_t cd;
        unsigned int rc, sz;

        rc = src->getReadByteCursor();
        sz = src->getWriteByteCursor();
        if( rc >= sz )
            return 0;

        cd = this->testSection( src, len );
        dest->writeUnalignedByte( cd, 3 );

        switch( cd )
        {
            case dpbuffer_deflate_no_compress:
                return this->writeUncompressed( src, dest, len );
            case dpbuffer_deflate_static_huffman:
                return 0;
            case dpbuffer_deflate_dynamic_huffman:
                return 0;
        }

        return 0;

    }

    //test next section
    uint8_t dpbuffer_deflate::testSection( dpbuffer *src, unsigned int len )
    {
        return dpbuffer_deflate_no_compress;
    }

    //read uncompressed section
    bool dpbuffer_deflate::readUncompressed( dpbuffer *src, dpbuffer *dest )
    {
        unsigned int rbyc, rbic;
        uint16_t sz, szr;

        rbyc = src->getReadByteCursor();
        rbic = src->getReadBitCursor();

        if( rbyc * 8 < rbic )
            rbyc += 1;
        src->setReadByteCursor( rbyc );

        if( !src->readAlignedBytes( (char *)&sz, sizeof( sz ) ) )
            return 0;
        if( !src->readAlignedBytes( (char *)&szr, sizeof( szr ) ) )
            return 0;

        dest->writeAlignedBytes( src, sz );
        src->setReadByteCursor( rbyc + sizeof( sz ) + sizeof( szr ) + sz );

        return 1;
    }

    //write uncompressed section
    bool dpbuffer_deflate::writeUncompressed( dpbuffer *src, dpbuffer *dest, unsigned int len )
    {
        unsigned int rbyc, rbic;
        uint16_t sz, szr;

        rbyc = dest->getWriteByteCursor();
        rbic = dest->getWriteBitCursor();

        if( rbyc * 8 < rbic )
            rbyc += 1;
        dest->setWriteByteCursor( rbyc );

        sz = src->getWriteByteCursor() - src->getReadByteCursor();
        if( sz > len )
            sz = len;

        sz = len;
        szr = ~sz;

        if( !dest->writeAlignedBytes( (char *)&sz, sizeof( sz ) ) )
            return 0;
        if( !dest->writeAlignedBytes( (char *)&szr, sizeof( szr ) ) )
            return 0;

        dest->writeAlignedBytes( src, sz );

        dest->setWriteByteCursor( rbyc + sizeof( sz ) + sizeof( szr ) + sz );
        return 1;
    }

};



