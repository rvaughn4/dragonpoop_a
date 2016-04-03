
/*

*/

#include "dpfont_filter.h"

namespace dp
{

    //ctor
    dpfont_filter::dpfont_filter( const char *cname )
    {
        this->b = 1;
        this->sname.assign( cname );
    }

    //dtor
    dpfont_filter::~dpfont_filter( void )
    {

    }

    //get name
    void dpfont_filter::getName( std::string *s )
    {
        s->assign( this->sname );
    }

    //disbale filter
    void dpfont_filter::enable( bool b )
    {
        this->b = b;
    }

    //returns true if enabled
    bool dpfont_filter::isEnabled( void )
    {
        return this->b;
    }

    //run filter
    unsigned int dpfont_filter::run( char *b, unsigned int sz, dpbitmap_position *pos_in, dpbitmap *dest_bmp, dpfont *fnt )
    {
        return 0;
    }

};

