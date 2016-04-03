
/*

*/

#include "dpbitmap_png.h"
#include "../../../dpcore/dpbuffer/dpbuffer_static/dpbuffer_static.h"
#include "../../../dpcore/dpbuffer/dpbuffer_zlib/dpbuffer_zlib.h"
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

        if( !b )
            return;

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
                        c->r = sb[ 0 ];
                        c->g = c->r;
                        c->b = c->r;
                        c->a = 65534;
                        break;
                    case dpbitmap_png_IHDR_color_truecolor:
                        c->r = sb[ 0 ];
                        c->g = sb[ 1 ];
                        c->b = sb[ 2 ];
                        c->a = 65534;
                        break;
                    case dpbitmap_png_IHDR_color_greyscale_alpha:
                        c->r = sb[ 0 ];
                        c->g = c->r;
                        c->b = c->r;
                        c->a = sb[ 1 ];
                        break;
                    case dpbitmap_png_IHDR_color_truecolor_alpha:
                        c->r = sb[ 0 ];
                        c->g = sb[ 1 ];
                        c->b = sb[ 2 ];
                        c->a = sb[ 3 ];
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

    uint8_t dpbitmap_png__parsePixels__left_x( uint8_t c, uint8_t a )
    {
        uint8_t r;

        r = c + a;

        return r;
    }

    void dpbitmap_png__parsePixels__left( unsigned int bpp, uint8_t *pc, uint8_t *pc_a )
    {
        unsigned int i;
        for( i = 0; i < bpp; i++ )
                pc[ i ] = dpbitmap_png__parsePixels__left_x( pc[ i ], pc_a[ i ] );
    }

    void dpbitmap_png__parsePixels__up( unsigned int bpp, uint8_t *pc, uint8_t *pc_b )
    {
        dpbitmap_png__parsePixels__left( bpp, pc, pc_b );
    }

    uint8_t dpbitmap_png__parsePixels__mean_x( uint32_t c, uint32_t a, uint32_t b )
    {
        uint32_t r;

        r = a + b;
        r = r / 2;

        r = r + c;

        return r;
    }

    void dpbitmap_png__parsePixels__mean( unsigned int bpp, uint8_t *c, uint8_t *c_a, uint8_t *c_b )
    {
        unsigned int i;

        for( i = 0; i < bpp; i++ )
            c[ i ] = dpbitmap_png__parsePixels__mean_x( c[ i ], c_a[ i ], c_b[ i ] );
    }

    uint8_t dpbitmap_png__parsePixels__pearth_x( int32_t a, int32_t b, int32_t c )
    {
        int32_t p, pa, pb, pc;

        p = a + b - c;

        pa = p - a;
        if( pa < 0 )
            pa *= -1;

        pb = p - b;
        if( pb < 0 )
            pb *= -1;

        pc = p - c;
        if( pc < 0 )
            pc *= -1;

        if( pa <= pb && pa <= pc )
            return a;

        if( pb <= pc )
            return b;

        return c;
    }

    void dpbitmap_png__parsePixels__pearth( unsigned int bpp, uint8_t *c, uint8_t *c_a, uint8_t *c_b, uint8_t *c_c )
    {
        unsigned int i;

        for( i = 0; i < bpp; i++ )
            c[ i ] = c[ i ] + dpbitmap_png__parsePixels__pearth_x( c_a[ i ], c_b[ i ], c_c[ i ] );
    }

    //parse nonpalette pixels
    bool dpbitmap_png::parsePixels( dpbitmap *b, unsigned int w, unsigned int h, unsigned int bits, unsigned int ctype )
    {
        dpbuffer_dynamic bs;
        unsigned int x, y, i, bpp, sz, pi;
        uint8_t fb;
        char *buf, *pc, *pc_a, *pc_b, *pc_c, dummy[ 128 ];
        dpbitmap_color c;

        if( bits != 8 && bits != 16 )
            return 0;
        this->decompPixels( &bs );
        memset( dummy, 0, sizeof( dummy ) );

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

            i = ( y * ( w * bpp + 1 ) );
            if( i < sz )
                fb = ((uint8_t *)buf)[ i ];

            pc = pc_a = pc_b = pc_c = dummy;

            for( x = 0; x < w; x++ )
            {
                i = ( y * ( w * bpp + 1 ) ) + 1 + x * bpp;
                if( i + bpp <= sz )
                    pc = &buf[ i ];
                if( x > 0 )
                {
                    pi = i - bpp;
                    if( pi + bpp < sz )
                        pc_a = &buf[ pi ];
                }
                if( y > 0 )
                {
                    pi = i - (w * bpp) - 1;
                    if( pi + bpp < sz )
                        pc_b = &buf[ pi ];
                }
                if( y > 0 && x > 0 )
                {
                    pi = i - (w * bpp) - 1;
                    pi = pi - bpp;
                    if( pi + bpp < sz )
                        pc_c = &buf[ pi ];
                }

                switch( fb )
                {
                    case 1:
                        dpbitmap_png__parsePixels__left( bpp, (uint8_t *)pc, (uint8_t *)pc_a );
                        break;
                    case 2:
                        dpbitmap_png__parsePixels__up( bpp, (uint8_t *)pc, (uint8_t *)pc_b );
                        break;
                    case 3:
                        dpbitmap_png__parsePixels__mean( bpp, (uint8_t *)pc, (uint8_t *)pc_a, (uint8_t *)pc_b );
                        break;
                    case 4:
                        dpbitmap_png__parsePixels__pearth( bpp, (uint8_t *)pc, (uint8_t *)pc_a, (uint8_t *)pc_b, (uint8_t *)pc_c );
                        break;
                }

                dpbitmap_png__parsePixels__a( &c, bits, ctype, pc );

                b->setPixel( x, y, &c );
            }
        }

        return 1;
    }

    //decompress pixel data
    bool dpbitmap_png::decompPixels( dpbuffer *pout )
    {
        dpbuffer_dynamic bs;
        dpbuffer_zlib d;

        if( !this->getIDAT( &bs ) )
            return 0;

        bs.setReadByteCursor( 0 );
        pout->setWriteByteCursor( 0 );
        return d.decompress( &bs, pout );
    }

    //compress image and overrwrite previous data
    bool dpbitmap_png::compress( dpbitmap *b )
    {
        unsigned int bits, ctype;

        bits = 8;
        ctype = dpbitmap_png_IHDR_color_truecolor_alpha;

        this->setWriteByteCursor( 0 );
        return this->genFileHdr()
        &&
        this->genIHDR( b->getWidth(), b->getHeight(), bits, ctype )
        &&
        this->genPLTE()
        &&
        this->genIDAT( b, bits, ctype )
        &&
        this->genIEND();
    }

    //generate default png header and chunks
    bool dpbitmap_png::genDefaults( int w, int h )
    {
        unsigned int bits, ctype;

        bits = 8;
        ctype = dpbitmap_png_IHDR_color_truecolor_alpha;

        return this->genFileHdr()
        &&
        this->genIHDR( w, h, bits, ctype )
        &&
        this->genPLTE()
        &&
        this->genIDAT( 0, bits, ctype )
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
    bool dpbitmap_png::genIHDR( unsigned int w, unsigned int h, unsigned int bits, unsigned int ctype )
    {
        dpbitmap_png_IHDR_outter hdr;
        dpbitmap_png_IHDR *c;

        hdr.c_start.type = *( (uint32_t *)"IHDR" );
        hdr.c_start.len = htonl( sizeof( dpbitmap_png_IHDR ) );
        hdr.c_end.crc = 0;
        c = &hdr.chnk;

        c->w = htonl( (unsigned int)w );
        c->h = htonl( (unsigned int)h );
        c->bits = bits;
        c->colorType = ctype;
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

    uint8_t dpbitmap_png__genIDAT_left_x( uint8_t c, uint8_t a )
    {
        return c - a;
    }

    void dpbitmap_png__genIDAT_left( unsigned int bpp, uint8_t *pc, uint8_t *pc_a )
    {
        unsigned int i;

        for( i = 0; i < bpp; i++ )
            pc[ i ] = dpbitmap_png__genIDAT_left_x( pc[ i ], pc_a[ i ] );
    }

    void dpbitmap_png__genIDAT_up( unsigned int bpp, uint8_t *pc, uint8_t *pc_b )
    {
        dpbitmap_png__genIDAT_left( bpp, pc, pc_b );
    }

    uint8_t dpbitmap_png__genIDAT_mean_x( uint32_t c, uint32_t a, uint32_t b )
    {
        uint32_t r;

        r = a + b;
        r = r >> 1;
        r = c - r;

        return r;
    }

    void dpbitmap_png__genIDAT_mean( unsigned int bpp, uint8_t *pc, uint8_t *pc_a, uint8_t *pc_b )
    {
        unsigned int i;

        for( i = 0; i < bpp; i++ )
            pc[ i ] = dpbitmap_png__genIDAT_mean_x( pc[ i ], pc_a[ i ], pc_b[ i ] );
    }

    uint8_t dpbitmap_png__genIDAT_pearth_x( int32_t a, int32_t b, int32_t c )
    {
        int32_t p, pa, pb, pc;

        p = a + b - c;

        pa = p - a;
        if( pa < 0 )
            pa *= -1;

        pb = p - b;
        if( pb < 0 )
            pb *= -1;

        pc = p - c;
        if( pc < 0 )
            pc *= -1;

        if( pa <= pb && pa <= pc )
            return a;

        if( pb <= pc )
            return b;

        return c;
    }

    void dpbitmap_png__genIDAT_pearth( unsigned int bpp, uint8_t *pc, uint8_t *pc_a, uint8_t *pc_b, uint8_t *pc_c )
    {
        unsigned int i;

        for( i = 0; i < bpp; i++ )
            pc[ i ] = pc[ i ] - dpbitmap_png__genIDAT_pearth_x( pc_a[ i ], pc_b[ i ], pc_c[ i ] );
    }

    void dpbitmap_png__genIDAT_conv( dpbitmap_color *c )
    {
        c->r *= 255.0f;
        c->g *= 255.0f;
        c->b *= 255.0f;
        c->a *= 255.0f;
    }

    void dpbitmap_png__genIDAT__a( dpbitmap_color *c, unsigned int bits, unsigned int ctype, char *b )
    {
        union
        {
            uint8_t *vb;
            uint16_t *sb;
            char *bb;
        };
        float f;

        if( !b )
            return;

        bb = b;
        switch( bits )
        {
            case 8:
            {
                c->r *= 255.0f;
                c->g *= 255.0f;
                c->b *= 255.0f;
                c->a *= 255.0f;

                switch( ctype )
                {
                    case dpbitmap_png_IHDR_color_greyscale:
                        f = c->r + c->g + c->b;
                        f *= 0.33f;
                        vb[ 0 ] = (uint8_t)f;
                        break;
                    case dpbitmap_png_IHDR_color_truecolor:
                        vb[ 0 ] = (uint8_t)c->r;
                        vb[ 1 ] = (uint8_t)c->g;
                        vb[ 2 ] = (uint8_t)c->b;
                        break;
                    case dpbitmap_png_IHDR_color_greyscale_alpha:
                        f = c->r + c->g + c->b;
                        f *= 0.33f;
                        vb[ 0 ] = (uint8_t)f;
                        vb[ 1 ] = (uint8_t)c->a;
                        break;
                    case dpbitmap_png_IHDR_color_truecolor_alpha:
                        vb[ 0 ] = (uint8_t)c->r;
                        vb[ 1 ] = (uint8_t)c->g;
                        vb[ 2 ] = (uint8_t)c->b;
                        vb[ 3 ] = (uint8_t)c->a;
                        break;
                }

                break;
            }
            case 16:
            {
                c->r *= 65534.0f;
                c->g *= 65534.0f;
                c->b *= 65534.0f;
                c->a *= 65534.0f;

                switch( ctype )
                {
                    case dpbitmap_png_IHDR_color_greyscale:
                        f = c->r + c->g + c->b;
                        f *= 0.33f;
                        sb[ 0 ] = (uint16_t)f;
                        break;
                    case dpbitmap_png_IHDR_color_truecolor:
                        sb[ 0 ] = (uint16_t)c->r;
                        sb[ 1 ] = (uint16_t)c->g;
                        sb[ 2 ] = (uint16_t)c->b;
                        break;
                    case dpbitmap_png_IHDR_color_greyscale_alpha:
                        f = c->r + c->g + c->b;
                        f *= 0.33f;
                        sb[ 0 ] = (uint16_t)f;
                        sb[ 1 ] = (uint16_t)c->a;
                        break;
                    case dpbitmap_png_IHDR_color_truecolor_alpha:
                        sb[ 0 ] = (uint16_t)c->r;
                        sb[ 1 ] = (uint16_t)c->g;
                        sb[ 2 ] = (uint16_t)c->b;
                        sb[ 3 ] = (uint16_t)c->a;
                        break;
                }

                break;
            }
        }
    }

    //generate default idat chunk
    bool dpbitmap_png::genIDAT( dpbitmap *bm, unsigned int bits, unsigned int ctype )
    {
        dpbitmap_png_chunk_start hs;
        dpbitmap_png_chunk_end he;
        dpbuffer_dynamic b, bd, b1;
        dpbuffer_zlib def;
        unsigned int w, h, x, y, bpp, sz, i, pi;
        dpbitmap_color c;
        uint8_t fv, *buf, *pc, *pc_a, *pc_b, *pc_c, dummy[ 64 ];

        fv = 4;
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

        w = h = 8;
        if( bm )
        {
            w = bm->getWidth();
            h = bm->getHeight();
        }
        sz = h * (w * bpp + 1);
        b.setWriteByteCursor( sz );
        b.writeAlignedByte( 0 );
        sz = b.getSize();
        buf = (uint8_t *)b.getBuffer();

        memset( dummy, 0, sizeof( dummy ) );

        for( y = 0; y < h; y++ )
        {
            for( x = 0; x < w; x++ )
            {
                i = ( y * ( w * bpp + 1 ) ) + 1 + x * bpp;
                pc = &buf[ i ];

                if( bm )
                    bm->getPixel( x, y, &c );
                dpbitmap_png__genIDAT__a( &c, bits, ctype, (char *)pc );
            }
        }

        for( y = h; y > 0; )
        {
            y--;

            i = y * (w * bpp + 1);
            if( i < sz )
                buf[ i ] = fv;

            for( x = w; x > 0; )
            {
                x--;
                pc = pc_a = pc_b = pc_c = dummy;

                i = ( y * ( w * bpp + 1 ) ) + 1 + x * bpp;
                if( i + bpp <= sz )
                    pc = &buf[ i ];
                if( x > 0 )
                {
                    pi = i - bpp;
                    if( pi + bpp < sz )
                        pc_a = &buf[ pi ];
                }
                if( y > 0 )
                {
                    pi = i - (w * bpp) - 1;
                    if( pi + bpp < sz )
                        pc_b = &buf[ pi ];
                }
                if( y > 0 && x > 0 )
                {
                    pi = i - (w * bpp) - 1;
                    pi = pi - bpp;
                    if( pi + bpp < sz )
                        pc_c = &buf[ pi ];
                }

                switch( fv )
                {
                    case 1: //subtracted from left
                        dpbitmap_png__genIDAT_left( bpp, pc, pc_a );
                        break;
                    case 2: //subtracted from up
                        dpbitmap_png__genIDAT_up( bpp, pc, pc_b );
                        break;
                    case 3: //average of a and b rounded down
                        dpbitmap_png__genIDAT_mean( bpp, pc, pc_a, pc_b );
                        break;
                    case 4: //pearth
                        dpbitmap_png__genIDAT_pearth( bpp, pc, pc_a, pc_b, pc_c );
                        break;
                }
            }
        }

        b.setReadByteCursor( 0 );
        bd.setWriteByteCursor( 0 );
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





