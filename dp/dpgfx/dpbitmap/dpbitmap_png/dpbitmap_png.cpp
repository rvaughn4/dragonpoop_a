
/*

*/

#include "dpbitmap_png.h"
#include "../../../dpcore/dpbuffer/dpbuffer_static/dpbuffer_static.h"
#include "../../../dpcore/dpbuffer/dpbuffer_deflate/dpbuffer_deflate.h"
#include <string.h>
#include <arpa/inet.h>

namespace dp
{

    //ctor
    dpbitmap_png::dpbitmap_png( int w, int h ) : dpbitmap_compressed( w, h )
    {
        this->genDefaults( w, h );
    }

    //ctor
    dpbitmap_png::dpbitmap_png( dpbuffer *b ) : dpbitmap_compressed( b )
    {

    }

    //dtor
    dpbitmap_png::~dpbitmap_png( void )
    {

    }

    //returns width
    int dpbitmap_png::getWidth( void )
    {
        dpbuffer_static b;
        dpbitmap_png_IHDR_outter *h;

        if( !this->getIHDR( &b ) )
            return 0;

        h = (dpbitmap_png_IHDR_outter *)b.getBuffer();
        return htonl(h->chnk.w);
    }

    //returns height
    int dpbitmap_png::getHeight( void )
    {
        dpbuffer_static b;
        dpbitmap_png_IHDR_outter *h;

        if( !this->getIHDR( &b ) )
            return 0;

        h = (dpbitmap_png_IHDR_outter *)b.getBuffer();
        return htonl(h->chnk.h);
    }

    //uncompress image and store in bitmap
    bool dpbitmap_png::uncompress( dpbitmap *b )
    {
        return 1;
    }

    //compress image and overrwrite previous data
    bool dpbitmap_png::compress( dpbitmap *b )
    {
        this->setWriteByteCursor( 0 );
        return this->genDefaults( b->getWidth(), b->getHeight() );
    }

    //generate default png header and chunks
    bool dpbitmap_png::genDefaults( int w, int h )
    {
        return this->genFileHdr()
        &&
        this->genIHDR( w, h )
        &&
        this->genPLTE()
        &&
        this->genIDAT()
        &&
        this->genIEND();
    }

    //generate default png file header
    bool dpbitmap_png::genFileHdr( void )
    {
        dpbitmap_png_file_hdr h;

        h.high_bit = 0x89;
        memcpy( (char *)&h.c_png[ 0 ], (char *)"PNG", 3 );
        h.c_crlf[ 0 ] = 0x0D;
        h.c_crlf[ 1 ] = 0x0A;
        h.c_eof = 0x1A;
        h.c_lf = 0x0A;

        return this->writeAlignedBytes( (char *)&h, sizeof( h ) );
    }

// ---------------------------- reverse --------------------------------

// Reverses (reflects) bits in a 32-bit word.
unsigned reverse(unsigned x) {
   x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
   x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
   x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
   x = (x << 24) | ((x & 0xFF00) << 8) |
       ((x >> 8) & 0xFF00) | (x >> 24);
   return x;
}

// ----------------------------- crc32a --------------------------------

/* This is the basic CRC algorithm with no optimizations. It follows the
logic circuit as closely as possible. */

unsigned int crc32a(unsigned char *message, int sz) {
   int i, j;
   unsigned int byte, crc;

   i = 0;
   crc = 0xFFFFFFFF;
   while ( i < sz )
    {
      byte = message[i];            // Get next byte.
      byte = reverse(byte);         // 32-bit reversal.
      for (j = 0; j <= 7; j++) {    // Do eight times.
         if ((int)(crc ^ byte) < 0)
              crc = (crc << 1) ^ 0x04C11DB7;
         else crc = crc << 1;
         byte = byte << 1;          // Ready next msg bit.
      }
      i = i + 1;
   }
   return reverse(~crc);
}

    //generate default png ihdr chunck
    bool dpbitmap_png::genIHDR( int w, int h )
    {
        dpbitmap_png_IHDR_outter hdr;
        dpbitmap_png_IHDR *c;

        hdr.c_start.type = *( (uint32_t *)"IHDR" );
        hdr.c_start.len = htonl( sizeof( dpbitmap_png_IHDR ) );
        hdr.c_end.crc = 0;
        c = &hdr.chnk;

        c->w = htonl( (unsigned int)w );
        c->h = htonl( (unsigned int)h );
        c->bits = 8;
        c->colorType = dpbitmap_png_IHDR_color_truecolor_alpha;
        c->filterType = 0;
        c->compType = 0;
        c->interlaceType = 0;

        hdr.c_end.crc = htonl(crc32a( (unsigned char *)&hdr.c_start.type, sizeof( hdr.c_start.type) + htonl(hdr.c_start.len) ));

        return this->writeAlignedBytes( (char *)&hdr, sizeof( hdr ) );
    }

    //generate default png plte chunk
    bool dpbitmap_png::genPLTE( void )
    {
        return 1;
    }

    //generate default idat chunk
    bool dpbitmap_png::genIDAT( void )
    {
        dpbitmap_png_chunk_start hs, *phs;
        dpbitmap_png_chunk_end he, *phe;
        dpbuffer_dynamic b, bd, b1;
        char *buf;
        dpbuffer_deflate def;
        float f;

        unsigned int w, h, x, y;

        w = 32;//this->getWidth();
        h = 32;//this->getHeight();

        b.writeAlignedByte( 0 );

        x = (w * 4 + 1) * h;
        b.writeAlignedBytes( (char *)&x, 2 );
        x = ~x;
        b.writeAlignedBytes( (char *)&x, 2 );

        for( y = 0; y < h; y++ )
        {
            b.writeAlignedByte( 0 );

            for( x = 0; x < w; x++ )
            {
                f = 255;//(float)y * 255.0f / (float)h;
                b.writeAlignedByte( f );
                f = 255;//(float)x * 255.0f / (float)w;
                b.writeAlignedByte( f );
                f = 255;
                b.writeAlignedByte( f );
                f = 255;
                b.writeAlignedByte( f );

                b.writeAlignedByte( f );
                b.writeAlignedByte( f );
                b.writeAlignedByte( f );
                b.writeAlignedByte( f );


            }
        }

       // def.compress( &b, &bd );

        hs.type = *( (uint32_t *)"IDAT" );
        hs.len = htonl( b.getSize() );
        he.crc = 0;

        b1.writeAlignedBytes( (char *)&hs, sizeof( hs ) );
        b1.writeAlignedBytes( &b );
        b1.writeAlignedBytes( (char *)&he, sizeof( he ) );

        buf = b1.getBuffer();
        phs = (dpbitmap_png_chunk_start *)buf;
        phe = (dpbitmap_png_chunk_end *)&buf[ htonl(phs->len) + sizeof( dpbitmap_png_chunk_start ) ];
        phe->crc = htonl( crc32a( (unsigned char *)&phs->type, htonl(phs->len) + sizeof( phs->type ) ) );

        return this->writeAlignedBytes( &b1 );
    }

    //generate default iend chunk
    bool dpbitmap_png::genIEND( void )
    {
        dpbitmap_png_IEND h;

        h.c_start.type = *( (uint32_t *)"IEND" );
        h.c_start.len = 0;
        h.c_end.crc = htonl( crc32a( (unsigned char *)&h.c_start.type, sizeof(h.c_start.type) ) );

        return this->writeAlignedBytes( (char *)&h, sizeof( h ) );
    }

    //get file header
    bool dpbitmap_png::getFileHeader( dpbuffer_static *b )
    {
        return this->getSection( b, 0, sizeof( dpbitmap_png_file_hdr ) );
    }

    //get IHDR chunck
    bool dpbitmap_png::getIHDR( dpbuffer_static *b )
    {
        return this->getSection( b, sizeof( dpbitmap_png_file_hdr ), sizeof(dpbitmap_png_IHDR_outter) );
    }

    //get PLTE chunck
    bool dpbitmap_png::getPLTE( dpbuffer_static *b )
    {
        unsigned int i, sz;

        if( !this->findChunk( "PLTE", 0, &i, &sz ) )
            return 0;

        return this->getSection( b, i, sz );
    }

    //get IDAT chuncks
    bool dpbitmap_png::getIHDR( dpbuffer_dynamic *b )
    {
        dpbuffer_static bs;
        unsigned int i, sz;

        i = 0;
        while( this->findChunk( "IHDR", i, &i, &sz ) )
        {
            if( !this->getSection( &bs, i + sizeof(dpbitmap_png_chunk_start), sz - sizeof(dpbitmap_png_chunk_start) - sizeof(dpbitmap_png_chunk_end) ) )
                return 1;
            i += sz;
            b->writeAlignedBytes( &bs );
        }

        return 1;
    }

    //get IEND chunck
    bool dpbitmap_png::getIEND( dpbuffer_static *b )
    {
        unsigned int i, sz;

        if( !this->findChunk( "IEND", 0, &i, &sz ) )
            return 0;

        return this->getSection( b, i, sz );
    }

    //find chunck offset and size
    bool dpbitmap_png::findChunk( const char *cname, unsigned int loc_start, unsigned int *ploc, unsigned int *psize )
    {
        dpbitmap_png_chunk_start *h;
        uint32_t id;
        unsigned int i, e, sl, sc;
        char *b;

        id = *( (uint32_t *)cname );
        e = this->getSize();
        b = this->getBuffer();

        i = loc_start;
        if( i < sizeof(dpbitmap_png_file_hdr) )
            i = sizeof(dpbitmap_png_file_hdr);

        while( i < e )
        {
            sl = e - i;
            if( sl < sizeof(dpbitmap_png_chunk_start) + sizeof(dpbitmap_png_chunk_end) )
                return 0;

            h = (dpbitmap_png_chunk_start *)&b[ i ];
            sc = sizeof(dpbitmap_png_chunk_start) + sizeof(dpbitmap_png_chunk_end) + h->len;
            if( sc > sl )
                return 0;
            if( h->type == id )
            {
                *ploc = i;
                *psize = sc;
                return 1;
            }

            i += sc;
        }

        return 0;
    }

};





