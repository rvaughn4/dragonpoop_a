
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

    //set pixel color
    bool dpbitmap_uncompressed::setPixel( int x, int y, dpbitmap_color *c )
    {
        dpbuffer_static bs;
        int scn, i, bpp, h;

        scn = this->getScanSize();
        bpp = this->getBits() / 8;
        h = this->getHeight();

        if( !this->getPixelData( &bs ) )
            return 0;

        if( h > 0 )
            y = h - y + 1;

        i = ( x * bpp ) + ( y * scn );

        bs.setWriteByteCursor( i );
        return this->writeColor( c, &bs );
    }

    //get pixel color
    bool dpbitmap_uncompressed::getPixel( int x, int y, dpbitmap_color *c )
    {
        dpbuffer_static bs;
        int scn, i, bpp, h;

        scn = this->getScanSize();
        bpp = this->getBits() / 8;
        h = this->getHeight();

        if( !this->getPixelData( &bs ) )
            return 0;

        if( h > 0 )
            y = h - y + 1;

        i = ( x * bpp ) + ( y * scn );

        bs.setReadByteCursor( i );
        return this->readColor( c, &bs );
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

        return hw->biHeight;
    }

    //get file header
    bool dpbitmap_uncompressed::getFileHeader( dpbuffer_static *b )
    {
        dpbitmap_uncompressed_file_header *h;

        if( this->getSize() <= sizeof( dpbitmap_uncompressed_file_header ) )
            return 0;

        h = (dpbitmap_uncompressed_file_header *)this->getBuffer();
        if( !h )
            return 0;

        b->setBuffer( (char *)h, sizeof( dpbitmap_uncompressed_file_header ) );
        return 1;
    }

    //get bitmap header
    bool dpbitmap_uncompressed::getBitmapHeader( dpbuffer_static *sb )
    {
        dpbitmap_uncompressed_core_header *h;
        char *b;

        if( this->getSize() <= sizeof( dpbitmap_uncompressed_file_header ) + sizeof(dpbitmap_uncompressed_core_header) )
            return 0;

        b = this->getBuffer();
        if( !b )
            return 0;

        h = (dpbitmap_uncompressed_core_header *)&b[ sizeof( dpbitmap_uncompressed_file_header ) ];
        if( h->bcSize + sizeof( dpbitmap_uncompressed_file_header ) > this->getSize() )
            return 0;

        sb->setBuffer( (char *)h, h->bcSize );
        return 1;
    }

    //get pixel data
    bool dpbitmap_uncompressed::getPixelData( dpbuffer_static *sb )
    {
        dpbitmap_uncompressed_file_header *fh;
        char *b;

        if( this->getSize() <= sizeof( dpbitmap_uncompressed_file_header ) + sizeof(dpbitmap_uncompressed_core_header) )
            return 0;

        b = this->getBuffer();
        if( !b )
            return 0;

        fh = (dpbitmap_uncompressed_file_header *)b;
        if( fh->bfSize > this->getSize() )
            return 0;

        sb->setBuffer( (char *)&b[ fh->bfOffBits ], fh->bfSize );//- fh->bfOffBits + 1 );
        return 1;
    }

    //get extra data
    bool dpbitmap_uncompressed::getExtraData( dpbuffer_static *b )
    {
        return 0;
    }

};




