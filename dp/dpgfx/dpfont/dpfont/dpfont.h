
/*
freetype 2 font
*/

#ifndef dpfont_h
#define dpfont_h

#include "../../dpbitmap/dpbitmap/dpbitmap.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include <string>

namespace dp
{

    class dpfont_filter;
    #define dpfont_max_filters 256

    class dpfont
    {

    private:

        FT_Library  lb;
        FT_Face fc;
        bool lb_loaded, fc_loaded;
        unsigned int sz;
        dpbitmap_color clr;
        dpfont_filter *filters[ dpfont_max_filters ];

        //zero filters
        void zeroFilters( void );
        //delete filters
        void deleteFilters( void );
        //run filters
        unsigned int runFilters( char *b, unsigned int len, dpbitmap_position *pos_in, dpbitmap *dest_bmp );

    protected:

    public:

        //ctor
        dpfont( void );
        //dtor
        virtual ~dpfont( void );
        //load font file, retains previous font if fails
        bool openFont( const char *fname );
        //draw a letter
        bool drawCharacter( unsigned char b, dpbitmap_position *pos_in, dpbitmap_rectangle *rect_sz_out, dpbitmap *dest_bmp );
        //draw a string
        bool drawString( char *b, unsigned int len, dpbitmap_rectangle *rect_in, dpbitmap_rectangle *rect_sz_out, dpbitmap *dest_bmp );
        //draw a string
        bool drawString( std::string *str, dpbitmap_rectangle *rect_in, dpbitmap_rectangle *rect_sz_out, dpbitmap *dest_bmp );
        //set font color
        void setColor( dpbitmap_color *c );
        //set font size
        bool setSize( unsigned int s );

    };

};

#endif
