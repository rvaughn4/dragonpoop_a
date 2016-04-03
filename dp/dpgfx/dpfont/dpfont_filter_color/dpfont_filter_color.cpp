
/*

*/

#include "dpfont_filter_color.h"
#include <sstream>
#include "../dpfont/dpfont.h"

namespace dp
{

    //ctor
    dpfont_filter_color::dpfont_filter_color( void ) : dpfont_filter( "color" )
    {

    }

    //dtor
    dpfont_filter_color::~dpfont_filter_color( void )
    {

    }

    unsigned int dpfont_filter_color__run_x( std::string *s )
    {
        std::stringstream ss;
        unsigned int r;

        ss << *s;
        ss >> std::hex >> r;

        return r;
    }

    //run filter
    unsigned int dpfont_filter_color::run( char *b, unsigned int sz, dpbitmap_position *pos_in, dpbitmap *dest_bmp, dpfont *fnt )
    {
        std::string s;
        dpbitmap_color clr;

        if( sz < 16 )
            return 0;
        if( b[ 0 ] != *"[" || b[ 15 ] != *"]" )
            return 0;

        s.assign( &b[ 1 ], 5 );
        if( s.compare( "color" ) != 0 )
            return 0;

        s.assign( &b[ 7 ], 2 );
        clr.r = dpfont_filter_color__run_x( &s );
        s.assign( &b[ 9 ], 2 );
        clr.g = dpfont_filter_color__run_x( &s );
        s.assign( &b[ 11 ], 2 );
        clr.b = dpfont_filter_color__run_x( &s );
        s.assign( &b[ 13 ], 2 );
        clr.a = dpfont_filter_color__run_x( &s );

        clr.r /= 256.0f;
        clr.g /= 256.0f;
        clr.b /= 256.0f;
        clr.a /= 256.0f;

        fnt->setColor( &clr );

        return 15;
    }

};


