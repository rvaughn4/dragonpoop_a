
/*

*/

#include "dpbitmap_24bit_uncompressed.h"
#include <string.h>

namespace dp
{

    int dpbitmap_24bit_uncompressed__header_size( void )
    {
        return sizeof( dpbitmap_uncompressed_core_header );
    }

    int dpbitmap_24bit_uncompressed__pixel_offset( void )
    {
        return sizeof( dpbitmap_uncompressed_file_header ) + dpbitmap_24bit_uncompressed__header_size();
    }

    int dpbitmap_24bit_uncompressed__file_size( int w, int h )
    {
        return dpbitmap_24bit_uncompressed__pixel_offset() + ( w * h * 4 );
    }

    //ctor
    dpbitmap_24bit_uncompressed::dpbitmap_24bit_uncompressed( int w, int h ) : dpbitmap_uncompressed( w, h, 24, dpbitmap_24bit_uncompressed__header_size(), dpbitmap_24bit_uncompressed__pixel_offset(), dpbitmap_24bit_uncompressed__file_size( w, h ) )
    {
        dpbuffer_static bs;
        dpbitmap_uncompressed_core_header *bh;

        if( !this->getBitmapHeader( &bs ) )
            return;

        bh = (dpbitmap_uncompressed_core_header *)bs.getBuffer();
        if( !bh || bs.getSize() < sizeof(dpbitmap_uncompressed_core_header) )
            return;

        memset( bh, 0, sizeof(dpbitmap_uncompressed_core_header) );

        bh->bcSize = sizeof(dpbitmap_uncompressed_core_header);
        bh->bcWidth = w;
        bh->bcHeight = h;
        bh->bcPlanes = 1;
        bh->bcBitCount = 24;
    }

    //ctor
    dpbitmap_24bit_uncompressed::dpbitmap_24bit_uncompressed( dpbuffer *b ) : dpbitmap_uncompressed( b )
    {

    }

    //dtor
    dpbitmap_24bit_uncompressed::~dpbitmap_24bit_uncompressed( void )
    {

    }

    //returns bits per pixel
    int dpbitmap_24bit_uncompressed::getBits( void )
    {
        return 24;
    }

    //returns scan line length
    unsigned int dpbitmap_24bit_uncompressed::getScanSize( void )
    {
        unsigned int w;

        w = this->getWidth() * 3;
        w = ( w & 3 ) + w;

        return w;
    }

    bool dpbitmap_24bit_uncompressed__writeColor__a( float c, dpbuffer *b )
    {
        uint8_t v;
        bool r;

        c = c * 255.0f;
        if( c > 255 )
            c = 255;
        v = (uint8_t)c;

        r = b->writeAlignedByte( v );
        if( !r )
            return 0;

        return r;
    }

    //write color to pointer
    bool dpbitmap_24bit_uncompressed::writeColor( dpbitmap_color *c, dpbuffer *b )
    {
        return
        dpbitmap_24bit_uncompressed__writeColor__a( c->b, b )
        &&
        dpbitmap_24bit_uncompressed__writeColor__a( c->g, b )
        &&
        dpbitmap_24bit_uncompressed__writeColor__a( c->r, b );
    }

    bool dpbitmap_24bit_uncompressed__readColor__a( float *c, dpbuffer *b )
    {
        uint8_t v;

        if( !b->readAlignedByte( &v ) )
            return 0;

        *c = (float)v / 256.0f;
        return 1;
    }

    //read color from pointer
    bool dpbitmap_24bit_uncompressed::readColor( dpbitmap_color *c, dpbuffer *b )
    {
        return
        dpbitmap_24bit_uncompressed__readColor__a( &c->b, b )
        &&
        dpbitmap_24bit_uncompressed__readColor__a( &c->g, b )
        &&
        dpbitmap_24bit_uncompressed__readColor__a( &c->r, b );
    }

};






