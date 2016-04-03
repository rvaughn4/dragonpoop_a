
/*

*/

#include "dpfont_filter_face.h"
#include <sstream>
#include "../dpfont/dpfont.h"

namespace dp
{

    //ctor
    dpfont_filter_face::dpfont_filter_face( void ) : dpfont_filter( "face" )
    {

    }

    //dtor
    dpfont_filter_face::~dpfont_filter_face( void )
    {

    }

    //run filter
    unsigned int dpfont_filter_face::run( char *b, unsigned int sz, dpbitmap_position *pos_in, dpbitmap *dest_bmp, dpfont *fnt )
    {
        std::string s;
        unsigned int i, nsz;

        if( sz < 6 )
            return 0;
        if( b[ 0 ] != *"[" )
            return 0;

        s.assign( &b[ 1 ], 4 );
        if( s.compare( "face" ) != 0 )
            return 0;

        nsz = sz;
        for( i = 5; i < nsz; i++ )
        {
            if( b[ i ] == *"]" )
                nsz = i;
        }
        if( i >= sz )
            return 0;

        s.assign( &b[ 6 ], i - 7 );

        fnt->openFont( s.c_str() );

        return i - 1;
    }

};




