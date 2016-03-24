
/*

*/

#include "dpbitmap_uncompressed_palette.h"
#include <string.h>

namespace dp
{

    int dpbitmap_uncompressed_palette__header_size( void )
    {
        return sizeof( dpbitmap_uncompressed_winv3_header );
    }

    int dpbitmap_uncompressed_palette__pixel_offset( int bits )
    {
        return sizeof( dpbitmap_uncompressed_file_header ) + dpbitmap_uncompressed_palette__header_size();
    }

    int dpbitmap_uncompressed_palette__scansize( int w, int bits )
    {
        int s;

        w *= bits;
        for( s = 32; s < w; s+= 32 );

        return s / 8;
    }

    int dpbitmap_uncompressed_palette__file_size( int w, int h, int bits )
    {
        return dpbitmap_uncompressed_palette__pixel_offset( bits ) + ( dpbitmap_uncompressed_palette__scansize( w, bits ) * h );
    }

    //ctor
    dpbitmap_uncompressed_palette::dpbitmap_uncompressed_palette( int w, int h, int bits ) :
    dpbitmap_uncompressed( w, h, bits, dpbitmap_uncompressed_palette__header_size(), dpbitmap_uncompressed_palette__pixel_offset( bits ), dpbitmap_uncompressed_palette__file_size( w, h, bits ) )
    {
        dpbuffer_static bs;
        dpbitmap_uncompressed_winv3_header *bh;
        unsigned int clrdim, r, g, b, i;
        dpbitmap_color c;

        if( !this->getBitmapHeader( &bs ) )
            return;

        bh = (dpbitmap_uncompressed_winv3_header *)bs.getBuffer();
        if( !bh || bs.getSize() < sizeof(dpbitmap_uncompressed_winv3_header) )
            return;

        memset( bh, 0, sizeof(dpbitmap_uncompressed_winv3_header) );

        bh->biSize = sizeof(dpbitmap_uncompressed_winv3_header);
        bh->biWidth = w;
        bh->biHeight = h;
        bh->biPlanes = 1;
        bh->biBitCount = bits;
        switch( bits )
        {
            case 1:
            case 2:
            case 4:
            default:
                clrdim = 6;
        }
        bh->biClrUsed = clrdim * clrdim * clrdim;
        bh->biClrImportant = bh->biClrUsed;

        c.a = 1;
        for( r = 0; r < clrdim; r++ )
        {
            c.r = (float)r / (float)clrdim;
            for( g = 0; g < clrdim; g++ )
            {
                c.g = (float)g / (float)clrdim;
                for( b = 0; b < clrdim; b++ )
                {
                    c.b = (float)b / (float)clrdim;

                    i = ( r * clrdim * clrdim ) + ( g * clrdim ) + b;
                    this->setPaletteColor( i, &c );
                }
            }
        }

    }

    //ctor
    dpbitmap_uncompressed_palette::dpbitmap_uncompressed_palette( dpbuffer *b ) : dpbitmap_uncompressed( b )
    {

    }

    //dtor
    dpbitmap_uncompressed_palette::~dpbitmap_uncompressed_palette( void )
    {

    }

    //return default red mask
    uint32_t dpbitmap_uncompressed_palette::getRedMask( void )
    {
        return 0;
    }

    //return default green mask
    uint32_t dpbitmap_uncompressed_palette::getGreenMask( void )
    {
        return 0;
    }

    //return default blue mask
    uint32_t dpbitmap_uncompressed_palette::getBlueMask( void )
    {
        return 0;
    }

    //return default alpha mask
    uint32_t dpbitmap_uncompressed_palette::getAlphaMask( void )
    {
        return 0;
    }

    //set pixel color
    bool dpbitmap_uncompressed_palette::setPixel( int x, int y, dpbitmap_color *c )
    {
        return 1;
    }

    //get pixel color
    bool dpbitmap_uncompressed_palette::getPixel( int x, int y, dpbitmap_color *c )
    {
        return 1;
    }

    //get palette data
    bool dpbitmap_uncompressed_palette::getPaletteData( dpbuffer_static *b )
    {
        dpbitmap_uncompressed_core_header *h;
        dpbitmap_uncompressed_file_header *fh;
        unsigned int s;

        if( !this->getSection( b, 0, sizeof(dpbitmap_uncompressed_file_header) ) )
           return 0;
        fh = (dpbitmap_uncompressed_file_header *)b->getBuffer();

        if( !this->getSection( b, sizeof( dpbitmap_uncompressed_file_header ), sizeof(dpbitmap_uncompressed_core_header) ) )
            return 0;
        h = (dpbitmap_uncompressed_core_header *)b->getBuffer();

        s = sizeof( dpbitmap_uncompressed_file_header ) + h->bcSize;
        return this->getSection( b, s, fh->bfOffBits - s );
    }

    //find closest color in palette
    bool dpbitmap_uncompressed_palette::findColor( uint32_t *r, dpbitmap_color *c )
    {
        unsigned int i, e, szp;
        dpbitmap_uncompressed_core_header *h;
        dpbuffer_static b;

        if( !this->getBitmapHeader( &b ) )
            return 0;
        h = (dpbitmap_uncompressed_core_header *)b.getBuffer();
        szp = 4;
        if( h->bcSize == sizeof( dpbitmap_uncompressed_core_header ) )
            szp = 3;

        *r = 0;
        e = 0;



        return 0;
    }

    //convert palette index to color
    bool dpbitmap_uncompressed_palette::getPaletteColor( uint32_t i, dpbitmap_color *c )
    {
        dpbitmap_uncompressed_core_header *h;
        dpbuffer_static b;
        unsigned int szp;
        uint8_t v;

        if( !this->getBitmapHeader( &b ) )
            return 0;
        h = (dpbitmap_uncompressed_core_header *)b.getBuffer();

        if( !this->getPaletteData( &b ) )
            return 0;

        szp = 4;
        if( h->bcSize == sizeof( dpbitmap_uncompressed_core_header ) )
            szp = 3;

        i *= szp;
        if( i >= b.getSize() )
            return 0;
        b.setWriteByteCursor( i );

        if( !b.readAlignedByte( &v ) )
            return 0;
        c->r = (float)v / 256.0f;
        if( !b.readAlignedByte( &v ) )
            return 0;
        c->g = (float)v / 256.0f;
        if( !b.readAlignedByte( &v ) )
            return 0;
        c->b = (float)v / 256.0f;

        return 1;
    }

    //set palette color
    bool dpbitmap_uncompressed_palette::setPaletteColor( uint32_t i, dpbitmap_color *c )
    {
        dpbitmap_uncompressed_core_header *h;
        dpbuffer_static b;
        unsigned int szp;
        float v;

        if( !this->getBitmapHeader( &b ) )
            return 0;
        h = (dpbitmap_uncompressed_core_header *)b.getBuffer();

        if( !this->getPaletteData( &b ) )
            return 0;

        szp = 4;
        if( h->bcSize == sizeof( dpbitmap_uncompressed_core_header ) )
            szp = 3;

        i *= szp;
        if( i >= b.getSize() )
            return 0;
        b.setWriteByteCursor( i );

        v = c->b * 255.0f;
        if( !b.writeAlignedByte( (uint8_t)v ) )
            return 0;
        v = c->g * 255.0f;
        if( !b.writeAlignedByte( (uint8_t)v ) )
            return 0;
        v = c->r * 255.0f;
        if( !b.writeAlignedByte( (uint8_t)v ) )
            return 0;
        if( szp == 4 && !b.writeAlignedByte( 0 ) )
            return 0;

        return 1;
    }

    //returns scan line length
    unsigned int dpbitmap_uncompressed_palette::getScanSize( void )
    {
        return dpbitmap_uncompressed_palette__scansize( this->getWidth(), this->getBits() );
    }

};







