
/*

*/

#include "dpbitmap_uncompressed.h"

namespace dp
{

    //ctor
    dpbitmap_uncompressed::dpbitmap_uncompressed( int w, int h, int bits, int bitmap_header_size, int offset_to_pixels, int file_size ) : dpbitmap()
    {
        dpbitmap_uncompressed_file_header fh;
        dpbitmap_uncompressed_core_header bh;

        fh.bfReserved1 = 0;
        fh.bfReserved2 = 0;
        fh.bfSize = file_size;
        fh.bfOffBits = offset_to_pixels;
        fh.bfType = *( (uint16_t *)"BM" );

        bh.bcSize = bitmap_header_size;
        bh.bcHeight = h;
        bh.bcWidth = w;
        bh.bcPlanes = 1;
        bh.bcBitCount = bits;

        this->setWriteByteCursor( 0 );
        this->writeAlignedBytes( (char *)&fh, sizeof( fh ) );
        this->writeAlignedBytes( (char *)&bh, sizeof( bh ) );
        this->setWriteByteCursor( file_size );
        this->writeAlignedByte( 0 );
    }

    //ctor
    dpbitmap_uncompressed::dpbitmap_uncompressed( dpbuffer *b ) : dpbitmap( b )
    {

    }

    //dtor
    dpbitmap_uncompressed::~dpbitmap_uncompressed( void )
    {

    }

    void dpbitmap_uncompressed__setPixel__a( uint32_t mask, float c, uint32_t *v )
    {
        uint32_t cntzeros, i;

        if( !mask )
            return;

        for( cntzeros = 0; ((mask >> cntzeros) & 1) == 0; cntzeros++ );

        i = mask >> cntzeros;
        c = c * (float)i;
        i = (uint32_t)c;
        i = i << cntzeros;
        i = i & mask;

        *v = *v | i;
    }

    //set pixel color
    bool dpbitmap_uncompressed::setPixel( int x, int y, dpbitmap_color *c )
    {
        dpbuffer_static bs;
        unsigned int scn, i, bpp, h, w;
        uint32_t v, rm, gm, bm, am;
        dpbitmap_uncompressed_winv3NT2_header *hdr;

        scn = this->getScanSize();
        bpp = this->getBits() / 8;
        w = this->getWidth();
        if( this->isUpsideDown( &h ) )
        {
            if( y < (int)h )
                y = h - y - 1;
        }
        if( y < 0 || y >= (int)h || x < 0 || x >= (int)w )
            return 1;

        i = ( x * bpp ) + ( y * scn );

        rm = this->getRedMask();
        gm = this->getGreenMask();
        bm = this->getBlueMask();
        am = this->getAlphaMask();

        if( !this->getBitmapHeader( &bs ) )
            return 0;
        hdr = (dpbitmap_uncompressed_winv3NT2_header *)bs.getBuffer();

        if( hdr->h.h.biSize >= sizeof(dpbitmap_uncompressed_winv3NT_header ) )
        {
            if( hdr->h.h.biCompression == dpbitmap_uncompressed_winv2_header_BI_BITFIELDS || hdr->h.h.biCompression == dpbitmap_uncompressed_winv3_header_BI_ALPHABITFIELDS )
            {
                rm = hdr->h.biRedMask;
                gm = hdr->h.biGreenMask;
                bm = hdr->h.biBlueMask;
                if( hdr->h.h.biSize >= sizeof(dpbitmap_uncompressed_winv3NT2_header ) )
                   am = hdr->biAlphaMask;
            }
        }

        if( !this->getPixelData( &bs ) )
            return 0;

        v = 0;
        dpbitmap_uncompressed__setPixel__a( rm, c->r, &v );
        dpbitmap_uncompressed__setPixel__a( gm, c->g, &v );
        dpbitmap_uncompressed__setPixel__a( bm, c->b, &v );
        dpbitmap_uncompressed__setPixel__a( am, c->a, &v );

        bs.setWriteByteCursor( i );
        return bs.writeAlignedBytes( (char *)&v, sizeof( v ) );
    }

    void dpbitmap_uncompressed__getPixel__a( uint32_t mask, float *c, uint32_t v )
    {
        uint32_t cntzeros, i;

        if( !mask )
            return;

        for( cntzeros = 0; ((mask >> cntzeros) & 1) == 0; cntzeros++ );

        if( cntzeros >= 32 )
        {
            *c = 1;
            return;
        }

        i = mask >> cntzeros;
        v = v & mask;
        v = v >> cntzeros;
        *c = (float)v;
        if( i != 0 )
            *c = *c / (float)i;
        else
            *c = 1;
    }

    //get pixel color
    bool dpbitmap_uncompressed::getPixel( int x, int y, dpbitmap_color *c )
    {
        dpbuffer_static bs;
        unsigned int scn, i, bpp, h, w;
        uint32_t v, rm, gm, bm, am;
        dpbitmap_uncompressed_winv3NT2_header *hdr;

        scn = this->getScanSize();
        bpp = this->getBits() / 8;
        w = this->getWidth();
        if( this->isUpsideDown( &h ) )
        {
            if( y < (int)h )
                y = h - y - 1;
        }
        if( y < 0 || y >= (int)h || x < 0 || x >= (int)w )
        {
            c->r = c->g = c->b = c->a = 0;
            return 1;
        }

        i = ( x * bpp ) + ( y * scn );
        rm = this->getRedMask();
        gm = this->getGreenMask();
        bm = this->getBlueMask();
        am = this->getAlphaMask();

        if( !this->getBitmapHeader( &bs ) )
            return 0;
        hdr = (dpbitmap_uncompressed_winv3NT2_header *)bs.getBuffer();

        if( hdr->h.h.biSize >= sizeof(dpbitmap_uncompressed_winv3NT_header ) )
        {
            if( hdr->h.h.biCompression == dpbitmap_uncompressed_winv2_header_BI_BITFIELDS || hdr->h.h.biCompression == dpbitmap_uncompressed_winv3_header_BI_ALPHABITFIELDS )
            {
                rm = hdr->h.biRedMask;
                gm = hdr->h.biGreenMask;
                bm = hdr->h.biBlueMask;
                if( hdr->h.h.biSize >= sizeof(dpbitmap_uncompressed_winv3NT2_header ) )
                   am = hdr->biAlphaMask;
            }
        }

        if( !this->getPixelData( &bs ) )
            return 0;

        bs.setReadByteCursor( i );
        v = 0;
        for( i = 0; i < bpp; i++ )
            bs.readAlignedByte( &( (uint8_t *)&v )[ i ] );

        dpbitmap_uncompressed__getPixel__a( rm, &c->r, v );
        dpbitmap_uncompressed__getPixel__a( gm, &c->g, v );
        dpbitmap_uncompressed__getPixel__a( bm, &c->b, v );
        dpbitmap_uncompressed__getPixel__a( am, &c->a, v );

        return 1;
    }

    //returns width
    int dpbitmap_uncompressed::getWidth( void )
    {
        dpbuffer_static bs;
        union
        {
            dpbitmap_uncompressed_core_header *hc;
            dpbitmap_uncompressed_winv3_header *hw;
        };

        if( !this->getBitmapHeader( &bs ) )
            return 0;

        if( bs.getSize() < sizeof(dpbitmap_uncompressed_core_header) )
            return 0;
        hw = (dpbitmap_uncompressed_winv3_header *)bs.getBuffer();
        if( !hw )
            return 0;

        if( hc->bcSize == sizeof( dpbitmap_uncompressed_core_header ) )
            return hc->bcWidth;

        return hw->biWidth;
    }

    //returns height
    int dpbitmap_uncompressed::getHeight( void )
    {
        dpbuffer_static bs;
        union
        {
            dpbitmap_uncompressed_core_header *hc;
            dpbitmap_uncompressed_winv3_header *hw;
        };

        if( !this->getBitmapHeader( &bs ) )
            return 0;

        if( bs.getSize() < sizeof(dpbitmap_uncompressed_core_header) )
            return 0;
        hw = (dpbitmap_uncompressed_winv3_header *)bs.getBuffer();
        if( !hw )
            return 0;

        if( hc->bcSize == sizeof( dpbitmap_uncompressed_core_header ) )
            return hc->bcHeight;

        if( hw->biHeight < 0 )
            return -hw->biHeight;
        return hw->biHeight;
    }

    //returns true if upside down, also gets height
    bool dpbitmap_uncompressed::isUpsideDown( unsigned int *h )
    {
        dpbuffer_static bs;
        union
        {
            dpbitmap_uncompressed_core_header *hc;
            dpbitmap_uncompressed_winv3_header *hw;
        };

        *h = 0;
        if( !this->getBitmapHeader( &bs ) )
            return 0;

        if( bs.getSize() < sizeof(dpbitmap_uncompressed_core_header) )
            return 0;
        hw = (dpbitmap_uncompressed_winv3_header *)bs.getBuffer();
        if( !hw )
            return 0;

        if( hc->bcSize == sizeof( dpbitmap_uncompressed_core_header ) )
        {
            *h = hc->bcHeight;
            return 1;
        }

        if( hw->biHeight > 0 )
        {
            *h = hw->biHeight;
            return 1;
        }

        *h = -hw->biHeight;
        return 0;
    }

    //get file header
    bool dpbitmap_uncompressed::getFileHeader( dpbuffer_static *b )
    {
        return this->getSection( b, 0, sizeof(dpbitmap_uncompressed_file_header) );
    }

    //get bitmap header
    bool dpbitmap_uncompressed::getBitmapHeader( dpbuffer_static *b )
    {
        dpbitmap_uncompressed_core_header *h;

        if( !this->getSection( b, sizeof( dpbitmap_uncompressed_file_header ), sizeof(dpbitmap_uncompressed_core_header) ) )
            return 0;
        h = (dpbitmap_uncompressed_core_header *)b->getBuffer();

        return this->getSection( b, sizeof( dpbitmap_uncompressed_file_header ), h->bcSize );
    }

    //get pixel data
    bool dpbitmap_uncompressed::getPixelData( dpbuffer_static *b )
    {
        dpbitmap_uncompressed_file_header *h;

        if( !this->getSection( b, 0, sizeof(dpbitmap_uncompressed_file_header) ) )
           return 0;
        h = (dpbitmap_uncompressed_file_header *)b->getBuffer();

        return this->getSection( b, h->bfOffBits, h->bfSize - h->bfOffBits );
    }

    //get extra data
    bool dpbitmap_uncompressed::getExtraData( dpbuffer_static *b )
    {
        dpbitmap_uncompressed_file_header *h;

        if( !this->getSection( b, 0, sizeof(dpbitmap_uncompressed_file_header) ) )
           return 0;
        h = (dpbitmap_uncompressed_file_header *)b->getBuffer();

        return this->getSection( b, h->bfSize, this->getSize() - h->bfSize );
    }

    //copy bitmap
    void dpbitmap_uncompressed::copy( dpbitmap *b )
    {
        unsigned int x, y, w, h;
        dpbitmap_color c;
        int otx, oty, ox, oy, sy, sx;

        w = b->getWidth();
        h = b->getHeight();

        this->getPixelOffset( &otx, &oty );
        b->getPixelOffset( &ox, &oy );

        for( y = 0; y < h; y++ )
        {
            for( x = 0; x < w; x++ )
            {
                sx = (int)x + otx;
                sy = (int)y + oty;
                b->getPixel( sx, sy, &c );

                sx = (int)x + ox;
                sy = (int)y + oy;
                this->setPixel( sx, sy, &c );
            }
        }
    }

};




