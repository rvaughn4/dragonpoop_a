
/*

*/

#include "dpbitmap_4bit_palette.h"

namespace dp
{

    //ctor
    dpbitmap_4bit_palette::dpbitmap_4bit_palette( int w, int h ) : dpbitmap_uncompressed_palette( w, h, 4 )
    {

    }

    //ctor
    dpbitmap_4bit_palette::dpbitmap_4bit_palette( dpbuffer *b ) : dpbitmap_uncompressed_palette( b )
    {

    }

    //dtor
    dpbitmap_4bit_palette::~dpbitmap_4bit_palette( void )
    {

    }

    //returns bits per pixel
    int dpbitmap_4bit_palette::getBits( void )
    {
        return 4;
    }

};








