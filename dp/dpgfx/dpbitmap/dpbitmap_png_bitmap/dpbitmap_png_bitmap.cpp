
/*

*/

#include "dpbitmap_png_bitmap.h"
#include "../dpbitmap_png/dpbitmap_png.h"
#include <string.h>

namespace dp
{

    //ctor
    dpbitmap_png_bitmap::dpbitmap_png_bitmap( int w, int h ) : dpbitmap_compressed( w, h )
    {
        this->png = new dpbitmap_png( w, h );
        this->compress( 0 );
    }

    //ctor
    dpbitmap_png_bitmap::dpbitmap_png_bitmap( dpbuffer *b ) : dpbitmap_compressed( b )
    {
        dpbuffer_static bs;

        this->png = new dpbitmap_png( 8, 8 );

        if( !this->getPixelData( &bs ) )
            return;

        this->png->load( &bs );
    }

    //dtor
    dpbitmap_png_bitmap::~dpbitmap_png_bitmap( void )
    {
        delete this->png;
    }

    //returns width
    int dpbitmap_png_bitmap::getWidth( void )
    {
        return this->png->getWidth();
    }

    //returns height
    int dpbitmap_png_bitmap::getHeight( void )
    {
        return this->png->getHeight();
    }

    //uncompress image and store in bitmap
    bool dpbitmap_png_bitmap::uncompress( dpbitmap *b )
    {
        b->copy( this->png );
        return 1;
    }

    //compress image and overrwrite previous data
    bool dpbitmap_png_bitmap::compress( dpbitmap *b )
    {
        dpbitmap_uncompressed_file_header fh;
        dpbitmap_uncompressed_winv3_header bh;
        unsigned int file_size, offset_to_pixels, image_size, bitmap_header_size;

        if( b )
            this->png->copy( b );

        offset_to_pixels = sizeof(dpbitmap_uncompressed_file_header) + sizeof(dpbitmap_uncompressed_winv3_header);
        image_size = this->png->getSize();
        file_size = image_size + offset_to_pixels;
        bitmap_header_size = sizeof(dpbitmap_uncompressed_winv3_header);

        fh.bfReserved1 = 0;
        fh.bfReserved2 = 0;
        fh.bfSize = file_size;
        fh.bfOffBits = offset_to_pixels;
        fh.bfType = *( (uint16_t *)"BM" );

        memset( &bh, 0, sizeof( bh ) );
        bh.biSize = bitmap_header_size;
        bh.biHeight = this->png->getHeight();
        bh.biWidth = this->png->getWidth();
        bh.biPlanes = 1;
        bh.biBitCount = 0;
        bh.biSizeImage = image_size;
        bh.biCompression = dpbitmap_uncompressed_winv1_header_BI_PNG;

        this->setWriteByteCursor( 0 );
        this->writeAlignedBytes( (char *)&fh, sizeof( fh ) );
        this->writeAlignedBytes( (char *)&bh, sizeof( bh ) );
        this->writeAlignedBytes( this->png );

        return 1;
    }

    //get file header
    bool dpbitmap_png_bitmap::getFileHeader( dpbuffer_static *b )
    {
        return this->getSection( b, 0, sizeof(dpbitmap_uncompressed_file_header) );
    }

    //get bitmap header
    bool dpbitmap_png_bitmap::getBitmapHeader( dpbuffer_static *b )
    {
        dpbitmap_uncompressed_core_header *h;

        if( !this->getSection( b, sizeof( dpbitmap_uncompressed_file_header ), sizeof(dpbitmap_uncompressed_core_header) ) )
            return 0;
        h = (dpbitmap_uncompressed_core_header *)b->getBuffer();

        return this->getSection( b, sizeof( dpbitmap_uncompressed_file_header ), h->bcSize );
    }

    //get pixel data
    bool dpbitmap_png_bitmap::getPixelData( dpbuffer_static *b )
    {
        dpbitmap_uncompressed_file_header *h;

        if( !this->getSection( b, 0, sizeof(dpbitmap_uncompressed_file_header) ) )
           return 0;
        h = (dpbitmap_uncompressed_file_header *)b->getBuffer();

        return this->getSection( b, h->bfOffBits, h->bfSize - h->bfOffBits );
    }

    //get extra data
    bool dpbitmap_png_bitmap::getExtraData( dpbuffer_static *b )
    {
        dpbitmap_uncompressed_file_header *h;

        if( !this->getSection( b, 0, sizeof(dpbitmap_uncompressed_file_header) ) )
           return 0;
        h = (dpbitmap_uncompressed_file_header *)b->getBuffer();

        return this->getSection( b, h->bfSize, this->getSize() - h->bfSize );
    }

};






