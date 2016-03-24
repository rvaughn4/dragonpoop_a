
/*

*/

#include "dpbitmap_8bit_palette.h"

namespace dp
{

    //ctor
    dpbitmap_8bit_palette::dpbitmap_8bit_palette( int w, int h ) : dpbitmap_uncompressed_palette( w, h, 8 )
    {

    }

    //ctor
    dpbitmap_8bit_palette::dpbitmap_8bit_palette( dpbuffer *b ) : dpbitmap_uncompressed_palette( b )
    {

    }

    //dtor
    dpbitmap_8bit_palette::~dpbitmap_8bit_palette( void )
    {

    }

    //returns bits per pixel
    int dpbitmap_8bit_palette::getBits( void )
    {
        return 8;
    }

};








