
/*

*/

#include "dpbitmap.h"
#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"

namespace dp
{

    //ctor
    dpbitmap::dpbitmap( void ) : dpbuffer_wrapper()
    {
        this->setWrapped( &this->int_b );
    }

    //ctor
    dpbitmap::dpbitmap( dpbuffer *b ) : dpbuffer_wrapper()
    {
        this->int_b.copy( b );
        this->setWrapped( &this->int_b );
    }

    //dtor
    dpbitmap::~dpbitmap( void )
    {

    }

    //load buffer from buffer
    bool dpbitmap::load( dpbuffer *b )
    {
        return this->dpbuffer_wrapper::load( b );
    }

    //load buffer from file
    bool dpbitmap::load( const char *fname )
    {
        return this->dpbuffer_wrapper::load( fname );
    }

    //save buffer to file
    bool dpbitmap::save( const char *fname )
    {
        return this->dpbuffer_wrapper::save( fname );
    }

    //save buffer to buffer
    bool dpbitmap::save( dpbuffer *b )
    {
        return this->dpbuffer_wrapper::save( b );
    }

    //get pixel offset
    void dpbitmap::getPixelOffset( int *x, int *y )
    {
        if( x )
            *x = 0;
        if( y )
            *y = 0;
    }


    //copy bitmap
    void dpbitmap::copy( dpbitmap *b )
    {
        dpbitmap_position p;
        p.x = p.y = 0;
        this->copyInto( b, &p );
    }

    void dpbitmap__copy__makeRect( dpbitmap *b, dpbitmap_position *r_pos_in, dpbitmap_rectangle *r_out )
    {
        dpbitmap_rectangle rc;

        rc.x = rc.y = 0;
        rc.w = b->getWidth();
        rc.h = b->getHeight();

        if( r_pos_in )
        {
            rc.x = r_pos_in->x;
            rc.y = r_pos_in->y;
            rc.w -= r_pos_in->x;
            rc.h -= r_pos_in->y;
        }

        *r_out = rc;
    }

    //copy bitmap into position
    void dpbitmap::copyInto( dpbitmap *b, dpbitmap_position *p_dest )
    {
        dpbitmap_rectangle p;
        dpbitmap__copy__makeRect( this, p_dest, &p );
        this->copyInto( b, &p );
    }

    //copy bitmap into rect
    void dpbitmap::copyInto( dpbitmap *b, dpbitmap_rectangle *p_dest )
    {
        dpbitmap_position p;
        p.x = p.y = 0;
        this->copy( b, &p, p_dest );
    }

    //copy bitmap from position
    void dpbitmap::copyFrom( dpbitmap *b, dpbitmap_position *p_src )
    {
        dpbitmap_rectangle p;
        dpbitmap__copy__makeRect( b, p_src, &p );
        this->copyFrom( b, &p );
    }

    //copy bitmap from rect
    void dpbitmap::copyFrom( dpbitmap *b, dpbitmap_rectangle *p_src )
    {
        dpbitmap_position p;
        p.x = p.y = 0;
        this->copy( b, p_src, &p );
    }

    //copy bitmap from position into position
    void dpbitmap::copy( dpbitmap *b, dpbitmap_position *p_src, dpbitmap_position *p_dest )
    {
        dpbitmap_rectangle p;
        dpbitmap__copy__makeRect( b, p_src, &p );
        this->copy( b, &p, p_dest );
    }

    //copy bitmap from rect into position
    void dpbitmap::copy( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_position *p_dest )
    {
        dpbitmap_rectangle p;
        dpbitmap__copy__makeRect( this, p_dest, &p );
        this->copy( b, p_src, &p );
    }

    //copy bitmap from position into rect
    void dpbitmap::copy( dpbitmap *b, dpbitmap_position *p_src, dpbitmap_rectangle *p_dest )
    {
        dpbitmap_rectangle p;
        dpbitmap__copy__makeRect( b, p_src, &p );
        this->copy( b, &p, p_dest );
    }

    void dpbitmap__copy__pixel( dpbitmap *bsrc, dpbitmap *bdest, int dx, int dy, int sx, int sy )
    {
        int dox, doy, sox, soy;
        dpbitmap_color c;

        bdest->getPixelOffset( &dox, &doy );
        bsrc->getPixelOffset( &sox, &soy );

        dx += sox;
        dy += soy;
        sx += dox;
        sy += doy;

        bsrc->getPixel( sx, sy, &c );
        bdest->setPixel( dx, dy, &c );
    }

    //copy bitmap from rect into rect
    void dpbitmap::copy( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_rectangle *p_dest )
    {
        int x, y, dx, dy, sx, sy;
        float fx, fy, rx, ry;

        ry = (float)p_src->h / (float)p_dest->h;
        rx = (float)p_src->w / (float)p_dest->w;

        for( y = 0; y < (int)p_dest->h; y++ )
        {
            fy = (float)y * ry;
            dy = y + p_dest->y;
            sy = (int)fy + p_src->y;

            for( x = 0; x < (int)p_dest->w; x++ )
            {
                fx = (float)x * rx;
                dx = x + p_dest->x;
                sx = (int)fx + p_src->x;

                dpbitmap__copy__pixel( b, this, dx, dy, sx, sy );
            }
        }
    }

    //copy without stretching to position
    void dpbitmap::copyNoStretch( dpbitmap *b, dpbitmap_position *p_dest )
    {
        dpbitmap_rectangle p;
        dpbitmap__copy__makeRect( b, 0, &p );
        this->copyNoStretch( b, &p, p_dest );
    }

    //copy without stretching to position
    void dpbitmap::copyNoStretch( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_position *p_dest )
    {
        int x, y, dx, dy, sx, sy;

        for( y = 0; y < (int)p_src->h; y++ )
        {
            dy = y + p_dest->y;
            sy = y + p_src->y;

            for( x = 0; x < (int)p_src->w; x++ )
            {
                dx = x + p_dest->x;
                sx = x + p_src->x;

                dpbitmap__copy__pixel( b, this, dx, dy, sx, sy );
            }
        }

    }

};



