
/*

*/

#include "dpfont_bitmap.h"

namespace dp
{

    //ctor
    dpfont_bitmap::dpfont_bitmap( dpbuffer *b ) : dpbitmap_uncompressed( b )
    {

    }

    //ctor
    dpfont_bitmap::dpfont_bitmap( FT_Library *lb, FT_Face *fc ) : dpbitmap_uncompressed( 8, 8, 32, 32, 32, 64 )
    {
        this->lb = *lb;
        this->fc = *fc;
    }

    //dtor
    dpfont_bitmap::~dpfont_bitmap( void )
    {

    }

    //returns width
    int dpfont_bitmap::getWidth( void )
    {
        int r;

        if( !this->fc->glyph )
            return 0;

        r = this->fc->glyph->bitmap.width;
        if( r < 0 )
            r *= -1;

        return r;
    }

    //returns height
    int dpfont_bitmap::getHeight( void )
    {
        int r;

        if( !this->fc->glyph )
            return 0;

        r = this->fc->glyph->bitmap.rows;
        if( r < 0 )
            r *= -1;

        return r;
    }

    //returns true if upside down, also gets height
    bool dpfont_bitmap::isUpsideDown( unsigned int *h )
    {
        if( h )
            *h = this->getHeight();
        return 0;
    }

    //returns bits per pixel
    int dpfont_bitmap::getBits( void )
    {
        return 8;
    }

    //returns scan line length
    unsigned int dpfont_bitmap::getScanSize( void )
    {
        int r;

        if( !this->fc->glyph )
            return 0;

        r = this->fc->glyph->bitmap.pitch;
        if( r < 0 )
            r *= -1;

        return r;
    }

    //get pixel data
    bool dpfont_bitmap::getPixelData( dpbuffer_static *b )
    {
        unsigned int s;

        if( !this->fc->glyph )
            return 0;

        s = this->getHeight() * this->getScanSize();
        if( !s )
            return 0;

        b->setBuffer( (char *)this->fc->glyph->bitmap.buffer, s );

        return 1;
    }

    //return default red mask
    uint32_t dpfont_bitmap::getRedMask( void )
    {
        return 0xFF;
    }

    //return default green mask
    uint32_t dpfont_bitmap::getGreenMask( void )
    {
        return 0xFF;
    }

    //return default blue mask
    uint32_t dpfont_bitmap::getBlueMask( void )
    {
        return 0xFF;
    }

    //return default alpha mask
    uint32_t dpfont_bitmap::getAlphaMask( void )
    {
        return 0xFF;
    }

};





