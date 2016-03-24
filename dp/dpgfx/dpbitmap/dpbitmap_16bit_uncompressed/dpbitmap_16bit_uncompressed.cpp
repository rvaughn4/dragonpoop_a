
/*

*/

#include "dpbitmap_16bit_uncompressed.h"
#include <string.h>

namespace dp
{

    int dpbitmap_16bit_uncompressed__header_size( void )
    {
        return sizeof( dpbitmap_uncompressed_winv3_header );
    }

    int dpbitmap_16bit_uncompressed__pixel_offset( void )
    {
        return sizeof( dpbitmap_uncompressed_file_header ) + dpbitmap_16bit_uncompressed__header_size();
    }

    int dpbitmap_16bit_uncompressed__scansize( int w )
    {
        int s;

        w *= 2;
        for( s = 4; s < w; s+= 4 );

        return s;
    }

    int dpbitmap_16bit_uncompressed__file_size( int w, int h )
    {
        return dpbitmap_16bit_uncompressed__pixel_offset() + ( dpbitmap_16bit_uncompressed__scansize( w ) * h );
    }

    //ctor
    dpbitmap_16bit_uncompressed::dpbitmap_16bit_uncompressed( int w, int h ) : dpbitmap_uncompressed( w, h, 16, dpbitmap_16bit_uncompressed__header_size(), dpbitmap_16bit_uncompressed__pixel_offset(), dpbitmap_16bit_uncompressed__file_size( w, h ) )
    {
        dpbuffer_static bs;
        dpbitmap_uncompressed_winv3_header *bh;

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
        bh->biBitCount = 16;
    }

    //ctor
    dpbitmap_16bit_uncompressed::dpbitmap_16bit_uncompressed( dpbuffer *b ) : dpbitmap_uncompressed( b )
    {

    }

    //dtor
    dpbitmap_16bit_uncompressed::~dpbitmap_16bit_uncompressed( void )
    {

    }

    //returns bits per pixel
    int dpbitmap_16bit_uncompressed::getBits( void )
    {
        return 16;
    }

    //returns scan line length
    unsigned int dpbitmap_16bit_uncompressed::getScanSize( void )
    {
        return dpbitmap_16bit_uncompressed__scansize( this->getWidth() );
    }

    //return default red mask
    uint32_t dpbitmap_16bit_uncompressed::getRedMask( void )
    {
        return 0x00007C00;
    }

    //return default green mask
    uint32_t dpbitmap_16bit_uncompressed::getGreenMask( void )
    {
        return 0x000003E0;
    }

    //return default blue mask
    uint32_t dpbitmap_16bit_uncompressed::getBlueMask( void )
    {
        return 0x0000001F;
    }

    //return default alpha mask
    uint32_t dpbitmap_16bit_uncompressed::getAlphaMask( void )
    {
        return 0;
    }

};






