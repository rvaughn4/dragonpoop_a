
/*

*/

#include "dpbitmap_32bit_uncompressed.h"
#include <string.h>

namespace dp
{

    int dpbitmap_32bit_uncompressed__header_size( void )
    {
        return sizeof( dpbitmap_uncompressed_winv4_header );
    }

    int dpbitmap_32bit_uncompressed__pixel_offset( void )
    {
        return sizeof( dpbitmap_uncompressed_file_header ) + dpbitmap_32bit_uncompressed__header_size();
    }

    int dpbitmap_32bit_uncompressed__file_size( int w, int h )
    {
        return dpbitmap_32bit_uncompressed__pixel_offset() + ( w * h * 4 );
    }

    //ctor
    dpbitmap_32bit_uncompressed::dpbitmap_32bit_uncompressed( int w, int h ) : dpbitmap_uncompressed( w, h, 32, dpbitmap_32bit_uncompressed__header_size(), dpbitmap_32bit_uncompressed__pixel_offset(), dpbitmap_32bit_uncompressed__file_size( w, h ) )
    {
        dpbuffer_static bs;
        dpbitmap_uncompressed_winv4_header *bh;

        if( !this->getBitmapHeader( &bs ) )
            return;

        bh = (dpbitmap_uncompressed_winv4_header *)bs.getBuffer();
        if( !bh || bs.getSize() < sizeof(dpbitmap_uncompressed_winv4_header) )
            return;

        memset( bh, 0, sizeof(dpbitmap_uncompressed_winv4_header) );

        bh->h.h.h.biSize = sizeof(dpbitmap_uncompressed_winv4_header);
        bh->h.h.h.biWidth = w;
        bh->h.h.h.biHeight = h;
        bh->h.h.h.biPlanes = 1;
        bh->h.h.h.biBitCount = 32;
        bh->h.h.h.biCompression = dpbitmap_uncompressed_winv2_header_BI_BITFIELDS;
        bh->h.h.h.biSizeImage = w * h * 4;
        bh->h.h.biRedMask = 0x00ff0000;
        bh->h.h.biGreenMask = 0x0000ff00;
        bh->h.h.biBlueMask = 0x000000ff;
        bh->h.biAlphaMask = 0xff000000;

    }

    //ctor
    dpbitmap_32bit_uncompressed::dpbitmap_32bit_uncompressed( dpbuffer *b ) : dpbitmap_uncompressed( b )
    {

    }

    //dtor
    dpbitmap_32bit_uncompressed::~dpbitmap_32bit_uncompressed( void )
    {

    }

    //returns bits per pixel
    int dpbitmap_32bit_uncompressed::getBits( void )
    {
        return 32;
    }

    //returns scan line length
    unsigned int dpbitmap_32bit_uncompressed::getScanSize( void )
    {
        return this->getWidth() * 4;
    }

    //return default red mask
    uint32_t dpbitmap_32bit_uncompressed::getRedMask( void )
    {
        return 0x00ff0000;
    }

    //return default green mask
    uint32_t dpbitmap_32bit_uncompressed::getGreenMask( void )
    {
        return 0x0000ff00;
    }

    //return default blue mask
    uint32_t dpbitmap_32bit_uncompressed::getBlueMask( void )
    {
        return 0x000000ff;
    }

    //return default alpha mask
    uint32_t dpbitmap_32bit_uncompressed::getAlphaMask( void )
    {
        return 0xff000000;
    }

};





