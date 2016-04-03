
/*
freetype 2 font
*/

#include "dpfont.h"
#include "../dpfont_filter/dpfont_filter.h"
#include "../dpfont_bitmap/dpfont_bitmap.h"

namespace dp
{

    //ctor
    dpfont::dpfont( void )
    {
        this->fc_loaded = 0;
        this->lb_loaded = 0;
        this->sz = 10;
        this->clr.r = this->clr.g = this->clr.b = 0;
        this->clr.a = 1;

        this->zeroFilters();
    }

    //dtor
    dpfont::~dpfont( void )
    {
        this->deleteFilters();

        if( this->fc_loaded )
            FT_Done_Face( this->fc );
        if( this->lb_loaded )
            FT_Done_FreeType( this->lb );
    }

    bool dpfont__openFont__x( const char **exts, unsigned int exts_sz, const char *font_name, FT_Face *fc, FT_Library *lb )
    {
        std::string s;
        unsigned int i;
        char c;

    //check for invalid characters or malicious shell code by rejected everything non alphanumeric
        s.assign( font_name );
        for( i = 0; i < (unsigned int)s.size(); i++ )
        {
            c = font_name[ i ];

            if( !
               (
                    ( c >= 48 && c <= 57 )
                    ||
                    ( c >= 65 && c <= 90 )
                    ||
                    ( c >= 97 && c <= 122 )
                    ||
                    ( c == 46 )
                    ||
                    ( c == 32 )
                )
               )
                return 0;
        }

    //try every extension
        for( i = 0; i < exts_sz; i++ )
        {
            s.assign( font_name );
            s.append( "." );
            s.append( exts[ i ] );
            if( FT_New_Face( *lb, s.c_str(), 0, fc ) == 0 )
                return 1;
        }

        return 0;
    }

    //load font file, retains previous font if fails
    bool dpfont::openFont( const char *fname )
    {
        FT_Face nfc;
        int h;

        if( !this->lb_loaded && !FT_Init_FreeType( &this->lb ) )
            this->lb_loaded = 1;
        if( !this->lb_loaded )
            return 0;

        const char *exts[] = { "ttf"/*1*/, "ttc"/*2*/, "otf"/*3*/, "fnt"/*4*/, "pfm"/*5*/, "afm"/*6*/, "dfont"/*7*/, "woff"/*8*/ };
        if( !dpfont__openFont__x( exts, 8, fname, &nfc, &this->lb ) )
            return 0;

        if( FT_Set_Pixel_Sizes( nfc, this->sz, 0 ) )
        {
            FT_Done_Face( nfc );
            return 0;
        }
        h = nfc->size->metrics.ascender - nfc->size->metrics.descender;
        if( h < 0 )
            h *= -1;
        this->sz = h / 108;

        if( this->fc_loaded )
            FT_Done_Face( this->fc );

        this->fc = nfc;
        this->fc_loaded = 1;
        return 1;
    }

    //draw a letter
    bool dpfont::drawCharacter( unsigned char b, dpbitmap_position *pos_in, dpbitmap_rectangle *rect_sz_out, dpbitmap *dest_bmp )
    {
        dpbitmap *bm;
        dpbitmap_position dp;

        if( !this->lb_loaded || !this->fc_loaded )
            return 0;

        if( FT_Load_Char( this->fc, b, FT_LOAD_RENDER ) )
            return 0;

        bm = new dpfont_bitmap( &this->lb, &this->fc, this->sz );
        if( !bm )
            return 0;

        if( !pos_in )
        {
            dp.x = dp.y = 0;
            pos_in = &dp;
        }

        if( dest_bmp )
            dest_bmp->copyNoStretch( bm, pos_in );

        if( rect_sz_out )
        {
            rect_sz_out->x = 0;
            rect_sz_out->y = 0;
            rect_sz_out->w = bm->getWidth();
            rect_sz_out->h = bm->getHeight();

            rect_sz_out->p = *pos_in;
        }

        delete bm;
        return 1;
    }

    //draw line, return count of characters in line including line breaks and filters, 0 is failure
    unsigned int dpfont::drawLine( char *b, unsigned int len, dpbitmap_rectangle *rect_in, dpbitmap *dest_bmp, unsigned int *lw )
    {
        unsigned int i, len_rem, r, last_sp;
        dpbitmap_position ip;
        char *c;
        dpbitmap_rectangle ir;

        if( !rect_in )
            return 0;

        ip = rect_in->p;
        last_sp = 0;
        for( i = 0; i < len; i++ )
        {
            c = &b[ i ];
            len_rem = len - i;
            *lw = ir.x;

            r = this->runFilters( c, len_rem, &ip, dest_bmp );
            if( r )
            {
                i += r;
                continue;
            }
            if( c[ 0 ] == 32 )
            {
                last_sp = i;
                ip.x += this->sz / 4;
                continue;
            }
            if( c[ 0 ] == *"\r" )
            {
                ip.x = 0;
                continue;
            }
            if( c[ 0 ] == *"\n" )
                return i + 1;

            if( !this->drawCharacter( (unsigned char)*c, &ip, &ir, 0 ) )
                return 0;
            if( ir.w + ir.x > rect_in->w + rect_in->x )
            {
                ip.x = rect_in->x;
                if( last_sp )
                    return last_sp + 1;
                return i;
            }

            if( !this->drawCharacter( (unsigned char)*c, &ip, &ir, dest_bmp ) )
                return 0;

            ip.x += ir.w;
        }

        return i;
    }

    //draw a string
    bool dpfont::drawString( char *b, unsigned int len, dpbitmap_rectangle *rect_in, dpbitmap_rectangle *rect_sz_out, dpbitmap *dest_bmp )
    {
        unsigned int i, r, len_rem, lw;
        char *c;
        dpbitmap_rectangle ir;

        if( rect_in )
            ir = *rect_in;
        else
        {
            ir.x = ir.y = 0;
            ir.w = dest_bmp->getWidth();
            ir.h = dest_bmp->getHeight();
        }

        for( i = 0; i < len; )
        {
            c = &b[ i ];
            len_rem = len - i;

            r = this->drawLine( c, len_rem, &ir, 0, &lw );
            if( !r )
                return 0;

        //do centering
            r = this->drawLine( c, r, &ir, dest_bmp, &lw );
            if( !r )
                return 0;
            ir.y += this->sz;
            ir.h -= this->sz;

            i += r;
        }
        if( rect_sz_out )
        {
            rect_sz_out->x = 0;
            rect_sz_out->y = 0;
            rect_sz_out->h = ir.y + this->sz;
            rect_sz_out->w = ir.x;

            if( rect_in )
            {
                rect_sz_out->x += rect_in->x;
                rect_sz_out->y += rect_in->y;
                rect_sz_out->w -= rect_in->x;
                rect_sz_out->h -= rect_in->y;
            }
        }

        return 1;
    }

    //draw a string
    bool dpfont::drawString( std::string *str, dpbitmap_rectangle *rect_in, dpbitmap_rectangle *rect_sz_out, dpbitmap *dest_bmp )
    {
        return this->drawString( (char *)str->c_str(), str->length(), rect_in, rect_sz_out, dest_bmp );
    }

    //set font color
    void dpfont::setColor( dpbitmap_color *c )
    {
        this->clr = *c;
    }

    //set font size
    bool dpfont::setSize( unsigned int s )
    {
        if( !this->fc_loaded || !this->lb_loaded )
        {
            this->sz = s;
            return 1;
        }

        if( FT_Set_Pixel_Sizes( this->fc, s, 0 ) )
            return 0;
        this->sz = this->fc->size->metrics.height / 108;

        this->sz = s;
        return 1;
    }

    //zero filters
    void dpfont::zeroFilters( void )
    {
        unsigned int i;

        for( i = 0; i < dpfont_max_filters; i++ )
            this->filters[ i ] = 0;
    }

    //delete filters
    void dpfont::deleteFilters( void )
    {
        unsigned int i;
        dpfont_filter *p;

        for( i = 0; i < dpfont_max_filters; i++ )
        {
            p = this->filters[ i ];
            if( !p )
                continue;
            //
        }

        this->zeroFilters();
    }

    //run filters
    unsigned int dpfont::runFilters( char *b, unsigned int len, dpbitmap_position *pos_in, dpbitmap *dest_bmp )
    {
        unsigned int i;
        dpfont_filter *p;

        for( i = 0; i < dpfont_max_filters; i++ )
        {
            p = this->filters[ i ];
            if( !p )
                continue;

            //
        }

        return 0;
    }

};

