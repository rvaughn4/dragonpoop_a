
/*

*/

#include "dpbuffer_zlib.h"
#include "../dpbuffer/dpbuffer.h"
#include "../../../../zlib/zlib.h"

namespace dp
{

    //ctor
    dpbuffer_zlib::dpbuffer_zlib( void )
    {

    }

    //dtor
    dpbuffer_zlib::~dpbuffer_zlib( void )
    {

    }

    //compress source buffer and output into dest buffer
    bool dpbuffer_zlib::compress( dpbuffer *src, dpbuffer *dest )
    {
        z_stream strm;
        int r;
        static unsigned int b_max = 60000;
        char b_out[ b_max ], *pb, *b_in;
        unsigned int i, sz, szi, doflush;

        pb = src->getBuffer();
        sz = src->getWriteByteCursor();
        if( !pb || !sz )
            return 0;

        strm.zalloc = 0;
        strm.zfree = 0;
        strm.opaque = 0;
        r = deflateInit( &strm, 8 );
        if( r != Z_OK )
            return 0;

        for( i = 0; i < sz; i += szi )
        {
            szi = sz - i;

            doflush = Z_NO_FLUSH;
            if( szi > b_max )
                szi = b_max;
            else
                doflush = Z_FINISH;

            b_in = &pb[ i ];

            strm.avail_in = szi;
            strm.next_in = (unsigned char *)b_in;

            do
            {
                strm.avail_out = b_max;
                strm.next_out = (unsigned char *)b_out;

                r = deflate( &strm, doflush );
                if( r == Z_STREAM_ERROR )
                {
                    deflateEnd( &strm );
                    return 0;
                }

                dest->writeAlignedBytes( b_out, b_max - strm.avail_out );
            }
            while( strm.avail_out == 0 );

            if( strm.avail_in != 0 )
            {
                deflateEnd( &strm );
                return 0;
            }
        }
        deflateEnd( &strm );

        return 1;
    }

    //decompress source buffer and output into dest buffer
    bool dpbuffer_zlib::decompress( dpbuffer *src, dpbuffer *dest )
    {
        z_stream strm;
        int r;
        static unsigned int b_max = 60000;
        char b_out[ b_max ], *pb, *b_in;
        unsigned int i, sz, szi, j, z;

        pb = src->getBuffer();
        sz = src->getWriteByteCursor();
        if( !pb || !sz )
            return 0;

        strm.zalloc = 0;
        strm.zfree = 0;
        strm.opaque = 0;
        strm.avail_in = 0;
        strm.next_in = 0;
        r = inflateInit( &strm );
        if( r != Z_OK )
            return 0;

        i = 0;
        do
        {

            szi = sz - i;
            if( szi > b_max )
                szi = b_max;
            b_in = &pb[ i ];
            i += szi;

            strm.avail_in = szi;
            strm.next_in = (unsigned char *)b_in;

            do
            {
                strm.avail_out = b_max;
                strm.next_out = (unsigned char *)b_out;

                r = inflate( &strm, Z_NO_FLUSH );
                switch( r )
                {
                    case Z_NEED_DICT:
                    case Z_MEM_ERROR:
                        inflateEnd( &strm );
                        return 0;
                    case Z_DATA_ERROR:
                        inflateEnd( &strm );
                        return 0;
                }

                dest->writeAlignedBytes( b_out, b_max - strm.avail_out );
            }
            while( strm.avail_out == 0 );

        }
        while( r != Z_STREAM_END && i < sz );

        inflateEnd( &strm );
        return 1;
    }

};



