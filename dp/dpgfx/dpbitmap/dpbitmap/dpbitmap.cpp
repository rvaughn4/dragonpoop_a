
/*

*/

#include "dpbitmap.h"
#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"
#include <math.h>

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

    void dpbitmap__copy__pixel_x( dpbitmap *bsrc, int sx, int sy, float fx, float fy, dpbitmap_color *c )
    {
        float mfx, mfy;
        dpbitmap_color tl, tr, bl, br;

        fx = fx - (float)sx;
        fy = fy - (float)sy;
        mfx = 1.0f - fx;
        mfy = 1.0f - fy;

        bsrc->getPixel( sx, sy, &tl );
        bsrc->getPixel( sx + 1, sy, &tr );
        bsrc->getPixel( sx, sy + 1, &bl );
        bsrc->getPixel( sx + 1, sy + 1, &br );

        c->r =  tl.r * mfx * mfy +
                tr.r * fx * mfy +
                bl.r * mfx * fy +
                br.r * fx * fy;
        c->g =  tl.g * mfx * mfy +
                tr.g * fx * mfy +
                bl.g * mfx * fy +
                br.g * fx * fy;
        c->b =  tl.b * mfx * mfy +
                tr.b * fx * mfy +
                bl.b * mfx * fy +
                br.b * fx * fy;
        c->a =  tl.a * mfx * mfy +
                tr.a * fx * mfy +
                bl.a * mfx * fy +
                br.a * fx * fy;
    }

    void dpbitmap__copy__pixel( dpbitmap *bsrc, dpbitmap *bdest, int dx, int dy, int sx, int sy, float fx, float fy )
    {
        int dox, doy, sox, soy;
        dpbitmap_color c, dc;
        float ca;

        bdest->getPixelOffset( &dox, &doy );
        bsrc->getPixelOffset( &sox, &soy );

        dx += sox;
        dy += soy;
        sx += dox;
        sy += doy;

        if( (float)sx == fx && (float)sy == fy )
            bsrc->getPixel( sx, sy, &c );
        else
            dpbitmap__copy__pixel_x( bsrc, sx, sy, fx, fy, &c );

        if( c.a < 0.01f )
            return;

        bdest->getPixel( dx, dy, &dc );

        ca = c.a;
        if( ca > 0.2f )
            ca = 1.0f;
        else
            ca = ca / 0.2f;

        c.r = c.r * c.a + dc.r * (1.0f - c.a);
        c.g = c.g * c.a + dc.g * (1.0f - c.a);
        c.b = c.b * c.a + dc.b * (1.0f - c.a);
        c.a = c.a * c.a + dc.a * (1.0f - c.a);

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

                dpbitmap__copy__pixel( b, this, dx, dy, sx, sy, fx + (float)p_src->x, fy + (float)p_src->y );
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

                dpbitmap__copy__pixel( b, this, dx, dy, sx, sy, sx, sy );
            }
        }

    }

};



