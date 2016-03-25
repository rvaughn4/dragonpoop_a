
/*

*/

#include "dpbitmap_1bit_palette.h"

namespace dp
{

    //ctor
    dpbitmap_1bit_palette::dpbitmap_1bit_palette( int w, int h ) : dpbitmap_uncompressed_palette( w, h, 1 )
    {

    }

    //ctor
    dpbitmap_1bit_palette::dpbitmap_1bit_palette( dpbuffer *b ) : dpbitmap_uncompressed_palette( b )
    {

    }

    //dtor
    dpbitmap_1bit_palette::~dpbitmap_1bit_palette( void )
    {

    }

    //returns bits per pixel
    int dpbitmap_1bit_palette::getBits( void )
    {
        return 1;
    }

};








