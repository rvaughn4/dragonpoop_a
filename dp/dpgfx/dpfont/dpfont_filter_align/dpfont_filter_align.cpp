
/*

*/

#include "dpfont_filter_align.h"
#include <sstream>
#include "../dpfont/dpfont.h"

namespace dp
{

    //ctor
    dpfont_filter_align::dpfont_filter_align( void ) : dpfont_filter( "align" )
    {

    }

    //dtor
    dpfont_filter_align::~dpfont_filter_align( void )
    {

    }

    //run filter
    unsigned int dpfont_filter_align::run( char *b, unsigned int sz, dpbitmap_position *pos_in, dpbitmap *dest_bmp, dpfont *fnt )
    {
        std::string s;
        unsigned int i, nsz;

        if( sz < 6 )
            return 0;
        if( b[ 0 ] != *"[" )
            return 0;

        s.assign( &b[ 1 ], 5 );
        if( s.compare( "align" ) != 0 )
            return 0;

        nsz = sz;
        for( i = 6; i < nsz; i++ )
        {
            if( b[ i ] == *"]" )
                nsz = i;
        }
        if( i >= sz )
            return 0;

        s.assign( &b[ 7 ], i - 8 );
        fnt->setAlignment( s.c_str() );

        return i - 1;
    }

};




