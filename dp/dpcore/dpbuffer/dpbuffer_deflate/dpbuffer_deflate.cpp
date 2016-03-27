
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

        //write zlib header
        dest->writeAlignedByte( 0x78 );
        dest->writeAlignedByte( 0x01 );

        while( this->writeSection( src, dest, 65000 ) )
            r = 1;

        return r;
    }

    //decompress source buffer and output into dest buffer
    bool dpbuffer_deflate::decompress( dpbuffer *src, dpbuffer *dest )
    {
        uint8_t v;

        src->readAlignedByte( &v );
        src->readAlignedByte( &v );

        while( this->readSection( src, dest ) );

        return 1;
    }

    //read next section
    bool dpbuffer_deflate::readSection( dpbuffer *src, dpbuffer *dest )
    {
        uint8_t cd;
        unsigned int rc, sz;
        bool r;

        rc = src->getReadByteCursor();
        sz = src->getWriteByteCursor();
        if( rc >= sz )
            return 0;

        cd = 0;
        if( !src->readUnalignedByte( &cd, 3 ) )
            return 0;

        r = !( cd & 1 );
        cd = cd >> 1;
        switch( cd )
        {
            case dpbuffer_deflate_no_compress:
                return this->readUncompressed( src, dest ) & r;
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

        cd = cd >> 1;
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
        uint8_t r;
        unsigned int rc, ln;

        rc = src->getReadByteCursor();
        ln = src->getWriteByteCursor();
        if( ln < rc )
            ln = 0;
        else
            ln = ln - rc;

        r = dpbuffer_deflate_no_compress;
        r = r << 1;
        if( ln < len )
            r = r | 1;
        else
            r = r & 0b110;

        return r;
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

        src->readAlignedBytes( (char *)&sz, sizeof( sz ) );
        src->readAlignedBytes( (char *)&szr, sizeof( szr ) );

        dest->writeAlignedBytes( src, sz );

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

        return 1;
    }

};



