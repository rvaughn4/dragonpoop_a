
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

    int dpbitmap_24bit_uncompressed__scansize( int w )
    {
        int s;

        w *= 3;
        for( s = 4; s < w; s+= 4 );

        return s;
    }

    int dpbitmap_24bit_uncompressed__file_size( int w, int h )
    {
        return dpbitmap_24bit_uncompressed__pixel_offset() + ( dpbitmap_24bit_uncompressed__scansize( w ) * h );
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
        return dpbitmap_24bit_uncompressed__scansize( this->getWidth() );
    }

    //return default red mask
    uint32_t dpbitmap_24bit_uncompressed::getRedMask( void )
    {
        return 0x00ff0000;
    }

    //return default green mask
    uint32_t dpbitmap_24bit_uncompressed::getGreenMask( void )
    {
        return 0x0000ff00;
    }

    //return default blue mask
    uint32_t dpbitmap_24bit_uncompressed::getBlueMask( void )
    {
        return 0x000000ff;
    }

    //return default alpha mask
    uint32_t dpbitmap_24bit_uncompressed::getAlphaMask( void )
    {
        return 0;
    }

};






