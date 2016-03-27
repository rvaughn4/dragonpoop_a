
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
        return this->genFileHdr()
        &&
        this->genIHDR( b->getWidth(), b->getHeight() )
        &&
        this->genPLTE()
        &&
        this->genIDAT( b )
        &&
        this->genIEND();
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
        this->genIDAT( 0 )
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

    float dpbitmap_png__genIDAT_pearth( float a, float b, float c )
    {
        float p, pa, pb, pc, r;

        p = a + b - c;

        r = a;
        pa = p - a;
        pa *= pa;

        pb = p - b;
        pb *= pb;
        if( pb < pa )
        {
            pa = pb;
            r = b;
        }

        pc = p - c;
        pc *= pc;
        if( pc < pa )
        {
            pa = pc;
            r = c;
        }

        return r;
    }

    void dpbitmap_png__genIDAT_conv( )
    {

    }

    //generate default idat chunk
    bool dpbitmap_png::genIDAT( dpbitmap *bm )
    {
        dpbitmap_png_chunk_start hs;
        dpbitmap_png_chunk_end he;
        dpbuffer_dynamic b, bd, b1;
        dpbuffer_deflate def;
        unsigned int w, h, x, y;
        dpbitmap_color c, c_a, c_b, c_c;
        float f;

        if( !bm )
            b.writeAlignedByte( 0 );
        else
        {
            w = bm->getWidth();
            h = bm->getHeight();

            for( y = 0; y < h; y++ )
            {
                b.writeAlignedByte( 4 );
                c_a.r = c_a.g = c_a.b = c_a.a = 0;
                c_c = c_b = c_a;

                for( x = 0; x < w; x++ )
                {
                    bm->getPixel( x, y, &c );
                    if( x > 0 )
                        bm->getPixel( x - 1, y, &c_a );
                    if( x > 0 && y > 0 )
                        bm->getPixel( x - 1, y - 1, &c_c );
                    if( y > 0 )
                        bm->getPixel( x, y - 1, &c_b );

                    c.r = c.r - dpbitmap_png__genIDAT_pearth( c_a.r, c_b.r, c_c.r );
                    c.g = c.g - dpbitmap_png__genIDAT_pearth( c_a.g, c_b.g, c_c.g );
                    c.b = c.b - dpbitmap_png__genIDAT_pearth( c_a.b, c_b.b, c_c.b );
                    c.a = c.a - dpbitmap_png__genIDAT_pearth( c_a.a, c_b.a, c_c.a );

                    b.writeAlignedByte( c.r );
                    b.writeAlignedByte( c.g );
                    b.writeAlignedByte( c.b );
                    b.writeAlignedByte( c.a );
                }
            }
        }

        b.setReadByteCursor( 0 );
        def.compress( &b, &bd );

        hs.type = *( (uint32_t *)"IDAT" );
        hs.len = htonl( bd.getSize() );

        b1.writeAlignedBytes( (char *)&hs, sizeof( hs ) );
        bd.setReadByteCursor( 0 );
        b1.writeAlignedBytes( &bd );
        he.crc = htonl( crc32a( (unsigned char *)b1.getBuffer() + 4, 4 + bd.getSize() ) );

        b1.setReadByteCursor( 0 );
        this->writeAlignedBytes( &b1 );
        this->writeAlignedBytes( (char *)&he, sizeof( he ) );

        return 1;
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





