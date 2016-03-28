
/*

*/

#include "dpbitmap_png.h"
#include "../../../dpcore/dpbuffer/dpbuffer_static/dpbuffer_static.h"
#include "../../../dpcore/dpbuffer/dpbuffer_deflate/dpbuffer_deflate.h"
#include "../dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"
#include "../dpbitmap_8bit_palette/dpbitmap_8bit_palette.h"
#include <string.h>
#include <arpa/inet.h>
#include <math.h>

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
        this->load( b );
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
        dpbuffer_static bs;
        dpbitmap_png_file_hdr *fh;
        dpbitmap_png_IHDR_outter *ihdr;
        uint32_t cv, tv, w, h, bits;
        dpbitmap *nb;
        uint8_t ctype;

        if( !this->getFileHeader( &bs ) )
            return 0;

        fh = (dpbitmap_png_file_hdr *)bs.getBuffer();
        tv = cv = 0;
        memcpy( (char *)&tv, (char *)&fh->c_png, 3 );
        memcpy( (char *)&cv, (char *)"PNG", 3 );
        if( tv != cv )
            return 0;

        if( !this->getIHDR( &bs ) )
            return 0;

        ihdr = (dpbitmap_png_IHDR_outter *)bs.getBuffer();
        w = htonl( ihdr->chnk.w );
        h = htonl( ihdr->chnk.h );
        bits = ihdr->chnk.bits;
        ctype = ihdr->chnk.colorType;

        nb = new dpbitmap_32bit_uncompressed( w, h );
        if( !nb )
            return 0;

        if( !this->parsePixels( nb, w, h, bits, ctype ) )
        {
            delete nb;
            return 0;
        }

        b->copy( nb );
        delete nb;

        return 1;
    }

    //parse paletted pixels
    bool dpbitmap_png::parsePalettePixels( dpbitmap *b, unsigned int w, unsigned int h, unsigned int bits, unsigned int ctype )
    {
        return 0;
    }

    void dpbitmap_png__parsePixels__a( dpbitmap_color *c, unsigned int bits, unsigned int ctype, char *b )
    {
        union
        {
            uint8_t *vb;
            uint16_t *sb;
            char *bb;
        };

        bb = b;
        switch( bits )
        {
            case 8:
            {
                switch( ctype )
                {
                    case dpbitmap_png_IHDR_color_greyscale:
                        c->r = vb[ 0 ];
                        c->g = c->r;
                        c->b = c->r;
                        c->a = 255;
                        break;
                    case dpbitmap_png_IHDR_color_truecolor:
                        c->r = vb[ 0 ];
                        c->g = vb[ 1 ];
                        c->b = vb[ 2 ];
                        c->a = 255;
                        break;
                    case dpbitmap_png_IHDR_color_greyscale_alpha:
                        c->r = vb[ 0 ];
                        c->g = c->r;
                        c->b = c->r;
                        c->a = vb[ 1 ];
                        break;
                    case dpbitmap_png_IHDR_color_truecolor_alpha:
                        c->r = vb[ 0 ];
                        c->g = vb[ 1 ];
                        c->b = vb[ 2 ];
                        c->a = vb[ 3 ];
                        break;
                }

                c->r = c->r / 256.0f;
                c->g = c->g / 256.0f;
                c->b = c->b / 256.0f;
                c->a = c->a / 256.0f;

                break;
            }
            case 16:
            {
                switch( ctype )
                {
                    case dpbitmap_png_IHDR_color_greyscale:
                        c->r = htons( vb[ 0 ] );
                        c->g = c->r;
                        c->b = c->r;
                        c->a = 65534;
                        break;
                    case dpbitmap_png_IHDR_color_truecolor:
                        c->r = htons( vb[ 0 ] );
                        c->g = htons( vb[ 1 ] );
                        c->b = htons( vb[ 2 ] );
                        c->a = 65534;
                        break;
                    case dpbitmap_png_IHDR_color_greyscale_alpha:
                        c->r = htons( vb[ 0 ] );
                        c->g = c->r;
                        c->b = c->r;
                        c->a = htons( vb[ 1 ] );
                        break;
                    case dpbitmap_png_IHDR_color_truecolor_alpha:
                        c->r = htons( vb[ 0 ] );
                        c->g = htons( vb[ 1 ] );
                        c->b = htons( vb[ 2 ] );
                        c->a = htons( vb[ 3 ] );
                        break;
                }

                c->r = c->r / 65534.0f;
                c->g = c->g / 65534.0f;
                c->b = c->b / 65534.0f;
                c->a = c->a / 65534.0f;

                break;
            }
        }
    }

    void dpbitmap_png__parsePixels__left( dpbitmap_color *c, dpbitmap_color *c_a )
    {
        c->r = c->r + c_a->r;
        c->g = c->g + c_a->g;
        c->b = c->b + c_a->b;
        c->a = c->a + c_a->a;
    }

    void dpbitmap_png__parsePixels__up( dpbitmap_color *c, dpbitmap_color *c_b )
    {
        c->r = c->r + c_b->r;
        c->g = c->g + c_b->g;
        c->b = c->b + c_b->b;
        c->a = c->a + c_b->a;
    }

    float dpbitmap_png__parsePixels__mean_x( float c, float a, float b )
    {
        float r;

        r = a + b;
        r = r * 0.5f;

        return c + floor( r );
    }

    void dpbitmap_png__parsePixels__mean( dpbitmap_color *c, dpbitmap_color *c_a, dpbitmap_color *c_b )
    {
        c->r = dpbitmap_png__parsePixels__mean_x( c->r, c_a->r, c_b->r );
        c->g = dpbitmap_png__parsePixels__mean_x( c->g, c_a->g, c_b->g );
        c->b = dpbitmap_png__parsePixels__mean_x( c->b, c_a->b, c_b->b );
        c->a = dpbitmap_png__parsePixels__mean_x( c->a, c_a->a, c_b->a );
    }

    float dpbitmap_png__parsePixels__pearth_x( float a, float b, float c )
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

    void dpbitmap_png__parsePixels__pearth( dpbitmap_color *c, dpbitmap_color *c_a, dpbitmap_color *c_b, dpbitmap_color *c_c )
    {
        c->r = c->r + dpbitmap_png__parsePixels__pearth_x( c_a->r, c_b->r, c_c->r );
        c->g = c->g + dpbitmap_png__parsePixels__pearth_x( c_a->g, c_b->g, c_c->g );
        c->b = c->b + dpbitmap_png__parsePixels__pearth_x( c_a->b, c_b->b, c_c->b );
        c->a = c->a + dpbitmap_png__parsePixels__pearth_x( c_a->a, c_b->a, c_c->a );
    }

    //parse nonpalette pixels
    bool dpbitmap_png::parsePixels( dpbitmap *b, unsigned int w, unsigned int h, unsigned int bits, unsigned int ctype )
    {
        dpbuffer_dynamic bs;
        unsigned int x, y, i, bpp, sz;
        uint8_t fb;
        char *buf;
        dpbitmap_color c, c_a, c_b, c_c;

        if( bits != 8 && bits != 16 )
            return 0;

        if( !this->decompPixels( &bs ) )
            return 0;

        switch( ctype )
        {
            case dpbitmap_png_IHDR_color_greyscale:
                bpp = bits;
                break;
            case dpbitmap_png_IHDR_color_truecolor:
                bpp = bits * 3;
                break;
            case dpbitmap_png_IHDR_color_indexed:
                return 0;
            case dpbitmap_png_IHDR_color_greyscale_alpha:
                bpp = bits * 2;
                break;
            case dpbitmap_png_IHDR_color_truecolor_alpha:
                bpp = bits * 4;
                break;
        }

        bpp = bpp / 8;
        buf = bs.getBuffer();
        sz = bs.getSize();

        for( y = 0; y < h; y++ )
        {
            c_a.r = c_a.g = c_a.b = c_a.a = 0;
            c_c = c_b = c_a;

            i = ( y * ( w * bpp + 1 ) ) + x * bpp;
            if( i < sz )
                fb = ((uint8_t *)buf)[ i ];

            for( x = 0; x < w; x++ )
            {
                i = ( y * ( w * bpp + 1 ) ) + 1 + x * bpp;
                if( i + bpp <= sz )
                    dpbitmap_png__parsePixels__a( &c, bits, ctype, &buf[ i ] );
                if( x > 0 )
                {
                    i = ( y * ( w * bpp + 1 ) ) + 1 + ( x - 1 ) * bpp;
                    if( i + bpp <= sz )
                        dpbitmap_png__parsePixels__a( &c_a, bits, ctype, &buf[ i ] );
                }
                if( y > 0 )
                {
                    i = ( ( y - 1 ) * ( w * bpp + 1 ) ) + 1 + x * bpp;
                    if( i + bpp <= sz )
                        dpbitmap_png__parsePixels__a( &c_b, bits, ctype, &buf[ i ] );
                }
                if( y > 0 && x > 0 )
                {
                    i = ( ( y - 1 ) * ( w * bpp + 1 ) ) + 1 + ( x - 1 ) * bpp;
                    if( i + bpp <= sz )
                        dpbitmap_png__parsePixels__a( &c_c, bits, ctype, &buf[ i ] );
                }

                switch( fb )
                {
                    case 1:
                        dpbitmap_png__parsePixels__left( &c, &c_a );
                        break;
                    case 2:
                        dpbitmap_png__parsePixels__up( &c, &c_b );
                        break;
                    case 3:
                        dpbitmap_png__parsePixels__mean( &c, &c_a, &c_b );
                        break;
                    case 4:
                        dpbitmap_png__parsePixels__pearth( &c, &c_a, &c_b, &c_c );
                        break;
                }

                b->setPixel( x, y, &c );
            }
        }

        return 1;
    }

    //decompress pixel data
    bool dpbitmap_png::decompPixels( dpbuffer *pout )
    {
        dpbuffer_dynamic bs;
        dpbuffer_deflate d;

        if( !this->getIDAT( &bs ) )
            return 0;

        return d.decompress( &bs, pout );
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

    // Reverses (reflects) bits in a 32-bit word.
    unsigned reverse(unsigned x)
    {
        x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
        x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
        x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
        x = (x << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | (x >> 24);
        return x;
    }

    //bad crc 32bit impl
    unsigned int crc32a( unsigned char *buffer, int sz )
    {
        int i, j;
        unsigned int byte, crc;

        crc = 0xFFFFFFFF;
        for( i = 0; i < sz; i++ )
        {
            byte = buffer[ i ];
            byte = reverse(byte);
            for( j = 0; j <= 7; j++ )
            {
                if( (int)( crc ^ byte ) < 0 )
                    crc = ( crc << 1 ) ^ 0x04C11DB7;
                else
                    crc = crc << 1;
                byte = byte << 1;
            }
        }
        return reverse( ~crc );
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

    void dpbitmap_png__genIDAT_left( dpbitmap_color *c, dpbitmap_color *c_a )
    {
        c->r = c->r - c_a->r;
        c->g = c->g - c_a->g;
        c->b = c->b - c_a->b;
        c->a = c->a - c_a->a;
    }

    void dpbitmap_png__genIDAT_up( dpbitmap_color *c, dpbitmap_color *c_b )
    {
        c->r = c->r - c_b->r;
        c->g = c->g - c_b->g;
        c->b = c->b - c_b->b;
        c->a = c->a - c_b->a;
    }

    float dpbitmap_png__genIDAT_mean_x( float c, float c_a, float c_b )
    {
        float r;

        r = c_a + c_b;
        r = r * 0.5f;

        return c - floor( r );
    }

    void dpbitmap_png__genIDAT_mean( dpbitmap_color *c, dpbitmap_color *c_a, dpbitmap_color *c_b )
    {
        c->r = dpbitmap_png__genIDAT_mean_x( c->r, c_a->r, c_b->r );
        c->g = dpbitmap_png__genIDAT_mean_x( c->g, c_a->g, c_b->g );
        c->b = dpbitmap_png__genIDAT_mean_x( c->b, c_a->b, c_b->b );
        c->a = dpbitmap_png__genIDAT_mean_x( c->a, c_a->a, c_b->a );
    }

    float dpbitmap_png__genIDAT_pearth_x( float a, float b, float c )
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

    void dpbitmap_png__genIDAT_pearth( dpbitmap_color *c, dpbitmap_color *c_a, dpbitmap_color *c_b, dpbitmap_color *c_c )
    {
        c->r -= dpbitmap_png__genIDAT_pearth_x( c_a->r, c_b->r, c_c->r );
        c->g -= dpbitmap_png__genIDAT_pearth_x( c_a->g, c_b->g, c_c->g );
        c->b -= dpbitmap_png__genIDAT_pearth_x( c_a->b, c_b->b, c_c->b );
        c->a -= dpbitmap_png__genIDAT_pearth_x( c_a->a, c_b->a, c_c->a );
    }

    void dpbitmap_png__genIDAT_conv( dpbitmap_color *c )
    {
        c->r *= 255.0f;
        c->g *= 255.0f;
        c->b *= 255.0f;
        c->a *= 255.0f;
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
        uint8_t fv;

        if( !bm )
            b.writeAlignedByte( 0 );
        else
        {
            w = bm->getWidth();
            h = bm->getHeight();
            fv = 4;

            for( y = 0; y < h; y++ )
            {
                b.writeAlignedByte( fv );
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

                    dpbitmap_png__genIDAT_conv( &c );
                    dpbitmap_png__genIDAT_conv( &c_a );
                    dpbitmap_png__genIDAT_conv( &c_b );
                    dpbitmap_png__genIDAT_conv( &c_c );

                    switch( fv )
                    {
                        case 1: //subtracted from left
                            dpbitmap_png__genIDAT_left( &c, &c_a );
                            break;
                        case 2: //subtracted from up
                            dpbitmap_png__genIDAT_up( &c, &c_b );
                            break;
                        case 3: //average of a and b rounded down
                            dpbitmap_png__genIDAT_mean( &c, &c_a, &c_b );
                            break;
                        case 4: //pearth
                            dpbitmap_png__genIDAT_pearth( &c, &c_a, &c_b, &c_c );
                            break;
                    }

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
    bool dpbitmap_png::getIDAT( dpbuffer_dynamic *b )
    {
        dpbuffer_static bs;
        unsigned int i, sz;

        dpbitmap_png_chunk_start *h;

        i = 0;
        while( this->findChunk( "IDAT", i, &i, &sz ) )
        {
            if( !this->getSection( &bs, i, sz ) )
                return 1;
            i += sz;
            h = (dpbitmap_png_chunk_start *)bs.getBuffer();
            h->len = htonl( h->len );
            bs.setReadByteCursor( sizeof(dpbitmap_png_chunk_start) );
            b->writeAlignedBytes( &bs, bs.getSize() - sizeof(dpbitmap_png_chunk_start) - sizeof(dpbitmap_png_chunk_end) );
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
            sc = sizeof(dpbitmap_png_chunk_start) + sizeof(dpbitmap_png_chunk_end) + htonl(h->len);
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





