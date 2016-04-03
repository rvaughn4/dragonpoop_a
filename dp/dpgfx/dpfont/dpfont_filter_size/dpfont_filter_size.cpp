
/*

*/

#include "dpfont_filter_size.h"
#include <sstream>
#include "../dpfont/dpfont.h"

namespace dp
{

    //ctor
    dpfont_filter_size::dpfont_filter_size( void ) : dpfont_filter( "size" )
    {

    }

    //dtor
    dpfont_filter_size::~dpfont_filter_size( void )
    {

    }

    unsigned int dpfont_filter_size__run_x( std::string *s )
    {
        std::stringstream ss;
        unsigned int r;

        ss << *s;
        ss  >> r;

        return r;
    }

    //run filter
    unsigned int dpfont_filter_size::run( char *b, unsigned int sz, dpbitmap_position *pos_in, dpbitmap *dest_bmp, dpfont *fnt )
    {
        std::string s;
        unsigned int i, nsz;

        if( sz < 6 )
            return 0;
        if( b[ 0 ] != *"[" )
            return 0;

        s.assign( &b[ 1 ], 4 );
        if( s.compare( "size" ) != 0 )
            return 0;

        nsz = sz;
        for( i = 5; i < nsz; i++ )
        {
            if( b[ i ] == *"]" )
                nsz = i;
        }
        if( i >= sz )
            return 0;

        s.assign( &b[ 5 ], i - 5 );
        nsz = dpfont_filter_size__run_x( &s );

        fnt->setSize( nsz );

        return i - 1;
    }

};



