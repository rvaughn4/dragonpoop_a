
/*

*/

#include "dpbitmap_loader.h"
#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"
#include "../dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"
#include "../dpbitmap_24bit_uncompressed/dpbitmap_24bit_uncompressed.h"
#include "../dpbitmap_16bit_uncompressed/dpbitmap_16bit_uncompressed.h"
#include "../dpbitmap_8bit_palette/dpbitmap_8bit_palette.h"
#include "../dpbitmap_4bit_palette/dpbitmap_4bit_palette.h"
#include "../dpbitmap_1bit_palette/dpbitmap_1bit_palette.h"
#include "../dpbitmap_png/dpbitmap_png.h"
#include "../dpbitmap_png_bitmap/dpbitmap_png_bitmap.h"
#include <string.h>

namespace dp
{

    //ctor
    dpbitmap_loader::dpbitmap_loader( void )
    {

    }

    //dtor
    dpbitmap_loader::~dpbitmap_loader( void )
    {

    }

    //parse buffer and generate correct bitmap object
    dpbitmap *dpbitmap_loader::load( dpbuffer *b )
    {
        dpbitmap *r;

        r = this->tryOS2Bitmap( b );
        if( r )
            return r;

        r = this->tryPng( b );
        if( r )
            return r;

        return 0;
    }

    //parse file and generate correct bitmap object
    dpbitmap *dpbitmap_loader::load( const char *fname )
    {
        dpbuffer_dynamic b;

        if( !b.load( fname ) )
            return 0;

        return this->load( &b );
    }

    //attemp windows style bitmap
    dpbitmap *dpbitmap_loader::tryOS2Bitmap( dpbuffer *b )
    {
        union
        {
            dpbitmap_uncompressed_file_header *fh;
            char *buf;
        };
        union
        {
            dpbitmap_uncompressed_core_header *ch;
            dpbitmap_uncompressed_winv3_header *wh;
        };
        unsigned int sz;

        fh = (dpbitmap_uncompressed_file_header *)b->getBuffer();
        sz = b->getSize();

        if( !fh || sz < sizeof(dpbitmap_uncompressed_file_header) + sizeof(dpbitmap_uncompressed_core_header) )
            return 0;

        if( fh->bfType != *( (uint16_t *)"BM" ) )
            return 0;

        ch = (dpbitmap_uncompressed_core_header *)&buf[ sizeof(dpbitmap_uncompressed_file_header) ];

        if( ch->bcSize < sizeof(dpbitmap_uncompressed_winv3_header) )
        {
            switch( ch->bcBitCount )
            {
                case 1:
                    return new dpbitmap_1bit_palette( b );
                case 4:
                    return new dpbitmap_4bit_palette( b );
                case 8:
                    return new dpbitmap_8bit_palette( b );
                case 16:
                    return new dpbitmap_16bit_uncompressed( b );
                case 24:
                    return new dpbitmap_24bit_uncompressed( b );
                case 32:
                    return new dpbitmap_32bit_uncompressed( b );
            }
            return 0;
        }

        if( wh->biCompression == dpbitmap_uncompressed_winv1_header_BI_PNG )
            return new dpbitmap_png_bitmap( b );
        if( wh->biCompression == dpbitmap_uncompressed_winv1_header_BI_JPEG )
            return 0;

        switch( wh->biBitCount )
        {
            case 1:
                return new dpbitmap_1bit_palette( b );
            case 4:
                return new dpbitmap_4bit_palette( b );
            case 8:
                return new dpbitmap_8bit_palette( b );
            case 16:
                return new dpbitmap_16bit_uncompressed( b );
            case 24:
                return new dpbitmap_24bit_uncompressed( b );
            case 32:
                return new dpbitmap_32bit_uncompressed( b );
        }
        return 0;
    }

    //attempt png
    dpbitmap *dpbitmap_loader::tryPng( dpbuffer *b )
    {
        dpbitmap_png_file_hdr *fh;
        unsigned int sz;
        uint32_t cv, tv;

        fh = (dpbitmap_png_file_hdr *)b->getBuffer();
        sz = b->getSize();

        if( !fh || sz < sizeof(dpbitmap_png_file_hdr) )
            return 0;

        tv = cv = 0;
        memcpy( (char *)&tv, (char *)&fh->c_png, 3 );
        memcpy( (char *)&cv, (char *)"PNG", 3 );

        if( tv != cv )
            return 0;

        return new dpbitmap_png( b );
    }

};




