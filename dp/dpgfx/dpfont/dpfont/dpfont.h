
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

    #define dpfont_align_left 0
    #define dpfont_align_center 1
    #define dpfont_align_right 2

    class dpfont
    {

    private:

        FT_Library  lb;
        FT_Face fc;
        bool lb_loaded, fc_loaded;
        unsigned int sz;
        dpbitmap_color clr;
        dpfont_filter *filters[ dpfont_max_filters ];
        int alignment;
        std::string sfname;

        //zero filters
        void zeroFilters( void );
        //delete filters
        void deleteFilters( void );
        //run filters
        unsigned int runFilters( char *b, unsigned int len, dpbitmap_position *pos_in, dpbitmap *dest_bmp );
        //draw line, return count of characters in line including line breaks and filters, 0 is failure
        unsigned int drawLine( char *b, unsigned int len, dpbitmap_rectangle *rect_in, dpbitmap *dest_bmp, unsigned int *p_width, unsigned int *p_height );

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
        //return size
        unsigned int getSize( void );
        //set alignment
        void setAlignment( int a );
        //get alignment
        int getAlignment( void );
        //set alignment
        void setAlignment( const char *c );
        //get font name
        void getName( std::string *s );
        //add filter
        void addFilter( dpfont_filter *f );

    };

};

#endif
