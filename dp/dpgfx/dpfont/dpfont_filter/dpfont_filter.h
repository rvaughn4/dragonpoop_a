
/*

*/

#ifndef dpfont_filter_h
#define dpfont_filter_h

#include "../../dpbitmap/dpbitmap/dpbitmap.h"
#include <string>

namespace dp
{

    class dpfont;

    class dpfont_filter
    {

    private:

        std::string sname;
        bool b;

    protected:

        //ctor
        dpfont_filter( const char *cname );

    public:

        //dtor
        virtual ~dpfont_filter( void );
        //get name
        void getName( std::string *s );
        //disbale filter
        void enable( bool b );
        //returns true if enabled
        bool isEnabled( void );
        //run filter
        virtual unsigned int run( char *b, unsigned int sz, dpbitmap_position *pos_in, dpbitmap *dest_bmp, dpfont *fnt );

    };

};

#endif
