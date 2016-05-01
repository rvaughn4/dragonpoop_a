
/*

*/

#include "dpbitmap.h"
#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"
#include <math.h>
#include <stdlib.h>

namespace dp
{

    //ctor
    dpbitmap::dpbitmap( void ) : dpbuffer_wrapper()
    {
        this->setWrapped( &this->int_b );

        this->transparency_mode = dpbitmap_transparency_mode_none;

        this->clr_mask.r = 1;
        this->clr_mask.g = 1;
        this->clr_mask.b = 1;
        this->clr_mask.a = 1;

        this->clr_clamp.r = 1;
        this->clr_clamp.g = 1;
        this->clr_clamp.b = 1;
        this->clr_clamp.a = 1;
    }

    //ctor
    dpbitmap::dpbitmap( dpbuffer *b ) : dpbuffer_wrapper()
    {
        this->int_b.copy( b );
        this->setWrapped( &this->int_b );

        this->transparency_mode = dpbitmap_transparency_mode_none;

        this->clr_mask.r = 1;
        this->clr_mask.g = 1;
        this->clr_mask.b = 1;
        this->clr_mask.a = 1;

        this->clr_clamp.r = 1;
        this->clr_clamp.g = 1;
        this->clr_clamp.b = 1;
        this->clr_clamp.a = 1;
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
        int dox, doy, sox, soy, tm;
        dpbitmap_color c, dc, cm, cc;

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
        tm = bdest->getTransparencyMode();

        if( c.a < 0.01f && tm == dpbitmap_transparency_mode_blend )
            return;

        bdest->getColorClamp( &cc );

        if( c.a < 0.99f )
        {
            if( c.a > cc.a )
                c.a = 1.0f;
            else
                c.a = c.a / cc.a;
        }
        if( c.a < 0.01f && tm == dpbitmap_transparency_mode_blend )
            return;

        if( c.r < 0.99f )
        {
            if( c.r > cc.r )
                c.r = 1.0f;
            else
                c.r = c.r / cc.r;
        }

        if( c.g < 0.99f )
        {
            if( c.g > cc.g )
                c.g = 1.0f;
            else
                c.g = c.g / cc.g;
        }

        if( c.b < 0.99f )
        {
            if( c.b > cc.b )
                c.b = 1.0f;
            else
                c.b = c.b / cc.b;
        }

        bdest->getColorMask( &cm );
        if( cm.r < 0.99f )
            c.r *= cm.r;
        if( cm.g < 0.99f )
            c.g *= cm.g;
        if( cm.b < 0.99f )
            c.b *= cm.b;
        if( cm.a < 0.99f )
            c.a *= cm.a;

        switch( tm )
        {
            case dpbitmap_transparency_mode_none:
                break;
            case dpbitmap_transparency_mode_blend:
                if( c.a < 0.99f )
                {
                    bdest->getPixel( dx, dy, &dc );
                    c.r = c.r * c.a + dc.r * (1.0f - c.a);
                    c.g = c.g * c.a + dc.g * (1.0f - c.a);
                    c.b = c.b * c.a + dc.b * (1.0f - c.a);
                    c.a = c.a * c.a + dc.a * (1.0f - c.a);
                }
                break;
            case dpbitmap_transparency_mode_mask:
                bdest->getPixel( dx, dy, &dc );
                c.r = c.r * dc.r;
                c.g = c.g * dc.g;
                c.b = c.b * dc.b;
                c.a = c.a * dc.a;
                c.r = c.r * c.a + dc.r * (1.0f - c.a);
                c.g = c.g * c.a + dc.g * (1.0f - c.a);
                c.b = c.b * c.a + dc.b * (1.0f - c.a);
                c.a = c.a * c.a + dc.a * (1.0f - c.a);
                break;
            case dpbitmap_transparency_mode_inverse_mask:
                bdest->getPixel( dx, dy, &dc );
                c.r = (1.0f - c.r) * dc.r;
                c.g = (1.0f - c.g) * dc.g;
                c.b = (1.0f - c.b) * dc.b;
                c.a = (1.0f - c.a) * dc.a;
                c.r = dc.r * c.a + c.r * (1.0f - c.a);
                c.g = dc.g * c.a + c.g * (1.0f - c.a);
                c.b = dc.b * c.a + c.b * (1.0f - c.a);
                c.a = dc.a * c.a + c.a * (1.0f - c.a);
                break;
        }

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

    //set color mask
    void dpbitmap::setColorMask( dpbitmap_color *c )
    {
        this->clr_mask = *c;
    }

    //get color mask
    void dpbitmap::getColorMask( dpbitmap_color *c )
    {
        *c = this->clr_mask;
    }

    //set color clamp
    void dpbitmap::setColorClamp( dpbitmap_color *c )
    {
        this->clr_clamp = *c;
    }

    //get color clamp
    void dpbitmap::getColorClamp( dpbitmap_color *c )
    {
        *c = this->clr_clamp;
    }

    //set transparency mode
    void dpbitmap::setTransparencyMode( int m )
    {
        this->transparency_mode = m;
    }

    //get transparency mode
    int dpbitmap::getTransparencyMode( void )
    {
        return this->transparency_mode;
    }

    //draw colored rectangle
    void dpbitmap::fill( dpbitmap_color *c )
    {
        dpbitmap_rectangle rc;

        rc.x = rc.y = 0;
        rc.w = this->getWidth();
        rc.h = this->getHeight();

        this->fill( c, &rc );
    }

    //draw colored rectangle
    void dpbitmap::fill( dpbitmap_color *c, dpbitmap_rectangle *rc )
    {
        int x, xm, y, ym;

        xm = rc->x + rc->w;
        ym = rc->y + rc->h;

        for( y = rc->y; y < ym; y++ )
            for( x = rc->x; x < xm; x++ )
                this->setPixel( x, y, c );
    }

    //clear rectanlge
    void dpbitmap::clear( void )
    {
        dpbitmap_color c;
        c.r = c.g = c.b = c.a = 0;
        this->fill( &c );
    }

    //clear rectanlge
    void dpbitmap::clear( dpbitmap_rectangle *rc )
    {
        dpbitmap_color c;
        c.r = c.g = c.b = c.a = 0;
        this->fill( &c, rc );
    }

    //draw rect with random noise
    void dpbitmap::noise( void )
    {
        dpbitmap_rectangle rc;

        rc.x = rc.y = 0;
        rc.w = this->getWidth();
        rc.h = this->getHeight();

        this->noise( &rc );
    }

    //draw rect with random noise
    void dpbitmap::noise( dpbitmap_rectangle *rc )
    {
        int x, xm, y, ym;
        dpbitmap_color c;

        xm = rc->x + rc->w;
        ym = rc->y + rc->h;

        for( y = rc->y; y < ym; y++ )
        {
            for( x = rc->x; x < xm; x++ )
            {
                c.r = (float)rand() / (float)RAND_MAX;
                c.g = (float)rand() / (float)RAND_MAX;
                c.b = (float)rand() / (float)RAND_MAX;
                c.a = (float)rand() / (float)RAND_MAX;
                this->setPixel( x, y, &c );
            }
        }
    }

    //alter rect with texture, pass in fineness in pixels
    void dpbitmap::texturize( float sz, float intensity )
    {
        dpbitmap_rectangle rc;

        rc.x = rc.y = 0;
        rc.w = this->getWidth();
        rc.h = this->getHeight();

        this->texturize( sz, intensity, &rc );
    }

    //alter rect with texture, pass in fineness in pixels
    void dpbitmap::texturize( float sz, float intensity, dpbitmap_rectangle *rc )
    {
        int x, xm, y, ym;
        dpbitmap_color c;
        float v, u, t;

        xm = rc->x + rc->w;
        ym = rc->y + rc->h;

        for( y = rc->y; y < ym; y++ )
        {
            for( x = rc->x; x < xm; x++ )
            {
                this->getPixel( x, y, &c );

                if( sz > 0.001f || sz < 0.001f )
                {
                    v = sin( (float)x / sz ) * sin( (float)y / sz );
                    if( v < 0 )
                        v *= -1.0f;
                    v *= 0.4f;

                    u = cos( (float)x / sz * 3 ) * cos( (float)y / sz * 11 );
                    if( u < 0 )
                        u *= -1.0f;
                    u *= 0.35f;

                    t = sin( (float)x / sz * 5 ) * sin( (float)y / sz * 7 );
                    if( t < 0 )
                        t *= -1.0f;
                    t *= 0.25f;

                    v = v + t + u;
                    v *= 0.5f + 0.5f * (float)rand() / (float)RAND_MAX;
                }
                else
                    v = 1;

                v = v * intensity + ( 1.0f - intensity );

                c.r *= v;
                c.g *= v;
                c.b *= v;

                this->setPixel( x, y, &c );
            }
        }
    }

    //create button effect
    void dpbitmap::buttonize( unsigned int border_width, float depth, bool bInvert )
    {
        dpbitmap_rectangle rc;

        rc.x = rc.y = 0;
        rc.w = this->getWidth();
        rc.h = this->getHeight();

        this->buttonize( border_width, depth, bInvert, &rc );
    }

    //create button effect
    void dpbitmap::buttonize( unsigned int border_width, float depth, bool bInvert, dpbitmap_rectangle *rc )
    {
        int x, xm, y, ym, xh, yh, dx, dy, xs, ys, sx, sy;
        dpbitmap_color c;
        float r, invdepth, gloss, xgloss, ygloss, e;

        if( depth > 1.0f )
            depth = 1.0f;
        invdepth = 1.0f - depth;

        xm = rc->x + rc->w;
        ym = rc->y + rc->h;
        xh = rc->x + rc->w / 2;
        yh = rc->y + rc->h / 2;
        xs = rc->x;
        ys = rc->y;

        for( sy = rc->y; sy < ym; sy++ )
        {
            y = sy;

            for( sx = rc->x; sx < xm; sx++ )
            {
                x = sx;

                this->getPixel( sx, sy, &c );

                if( x < xh )
                    dx = x - xs;
                else
                    dx = xm - x;
                if( y < yh )
                    dy = y - ys;
                else
                    dy = ym - y;
                if( dx > (int)border_width )
                    dx = border_width;
                if( dy > (int)border_width )
                    dy = border_width;

                if( bInvert )
                {
                    x = ( xm - rc->x ) - ( sx - rc->x ) + rc->x;
                    y = ( ym - rc->y ) - ( sy - rc->y ) + rc->y;
                }

                if( dy < dx )
                    r = dy;
                else
                    r = dx;
                r = r / (float)border_width;
                r = r * depth + invdepth;

                ygloss = xgloss = 0;
                if( x < xs + (int)border_width && ym - y > x - xs )
                {
                    if( ym - y > (int)border_width )
                        xgloss = ( (float)x - (float)xs ) / (float)border_width;
                    else
                    {
                        if( ym != y )
                            xgloss = ( (float)x - (float)xs ) / ( (float)ym - (float)y );
                        else
                            xgloss = 1;
                    }
                    xgloss = ( 1.0f - xgloss ) * ( 1.0f - r );
                }
                if( y < ys + (int)border_width && xm - x > y - ys )
                {
                    if( xm - x > (int)border_width )
                        ygloss = ( (float)y - (float)ys ) / (float)border_width;
                    else
                    {
                        if( xm != x )
                            ygloss = ( (float)y - (float)ys ) / ( (float)xm - (float)x );
                        else
                            ygloss = 1;
                    }
                    ygloss = ( 1.0f - ygloss ) * ( 1.0f - r );
                }

                gloss = ( xgloss + ygloss ) / 1.5f;
                if( xgloss > gloss )
                    gloss = xgloss;
                if( ygloss > gloss )
                    gloss = ygloss;

                e = 1.0f - this->getEdgeDetectValue( sx, sy );
                gloss = gloss * 0.5f + ( gloss * 0.5f * e );
                r = ( 1.0f - r );
                r = r * 0.5f + ( r * 0.5f * e );
                r = ( 1.0f - r );

                c.r = c.r * r + gloss;
                c.g = c.g * r + gloss;
                c.b = c.b * r + gloss;

                if( c.r > 1.0f )
                    c.r = 1.0f;
                if( c.g > 1.0f )
                    c.g = 1.0f;
                if( c.b > 1.0f )
                    c.b = 1.0f;
                if( c.r < 0.0f )
                    c.r = 0.0f;
                if( c.g < 0.0f )
                    c.g = 0.0f;
                if( c.b < 0.0f )
                    c.b = 0.0f;

                this->setPixel( sx, sy, &c );
            }
        }
    }

    //get edge detection value at pixel
    float dpbitmap::getEdgeDetectValue( int x, int y )
    {
        int xa, ya;
        dpbitmap_color ca, c;
        float r;

        xa = x + 1;
        ya = y + 1;

        this->getPixel( xa, ya, &ca );
        this->getPixel( x, y, &c );

        r = c.r - ca.r;
        r += c.g - ca.g;
        r += c.b - ca.b;

        if( r > 1.0f )
            r = 1.0f;
        if( r < 0.0f )
            r = 0.0f;

        return r;
    }

    //create edge detect effect
    void dpbitmap::edgeDetect( float ratio, bool bInvert )
    {
        dpbitmap_rectangle rc;

        rc.x = rc.y = 0;
        rc.w = this->getWidth();
        rc.h = this->getHeight();

        this->edgeDetect( ratio, bInvert, &rc );
    }

    //create edge detect effect
    void dpbitmap::edgeDetect( float ratio, bool bInvert, dpbitmap_rectangle *rc )
    {
        int x, xm, y, ym;
        dpbitmap_color c, ca;
        float f, r, ir;

        r = ratio;
        ir = 1.0f - r;

        xm = rc->x + rc->w;
        ym = rc->y + rc->h;

        for( y = rc->y; y < ym; y++ )
        {
            for( x = rc->x; x < xm; x++ )
            {
                this->getPixel( x, y, &c );
                this->getPixel( x + 1, y + 1, &ca );

                f = c.r - ca.r;
                f += c.g - ca.g;
                f += c.b - ca.b;
                f += c.a - ca.a;
                if( f > 1.0f )
                    f = 1.0f;
                if( f < -1.0f )
                    f = -1.0f;
                if( bInvert )
                    f = ( 2.0f - ( f + 1.0f ) ) - 1.0f;

                c.r = f * r + c.r * ir;
                c.g = f * r + c.g * ir;
                c.b = f * r + c.b * ir;

                if( c.r > 1.0f )
                    c.r = 1.0f;
                if( c.g > 1.0f )
                    c.g = 1.0f;
                if( c.b > 1.0f )
                    c.b = 1.0f;
                if( c.r < 0.0f )
                    c.r = 0.0f;
                if( c.g < 0.0f )
                    c.g = 0.0f;
                if( c.b < 0.0f )
                    c.b = 0.0f;

                this->setPixel( x, y, &c );
            }
        }
    }

    //sharpen or blur image
    void dpbitmap::sharpen( float mult )
    {
        dpbitmap_rectangle rc;

        rc.x = rc.y = 0;
        rc.w = this->getWidth();
        rc.h = this->getHeight();

        this->sharpen( mult, &rc );
    }

    //sharpen or blur image
    void dpbitmap::sharpen( float mult, dpbitmap_rectangle *rc )
    {
        int x, xm, y, ym;
        dpbitmap_color c, ca;

        xm = rc->x + rc->w;
        ym = rc->y + rc->h;

        for( y = rc->y; y < ym; y++ )
        {
            for( x = rc->x; x < xm; x++ )
            {
                this->getPixel( x, y, &c );
                this->getPixel( x + 1, y + 1, &ca );

                c.r += ( c.r - ca.r ) * mult;
                c.g += ( c.g - ca.g ) * mult;
                c.b += ( c.b - ca.b ) * mult;

                if( c.r > 1.0f )
                    c.r = 1.0f;
                if( c.g > 1.0f )
                    c.g = 1.0f;
                if( c.b > 1.0f )
                    c.b = 1.0f;
                if( c.r < 0.0f )
                    c.r = 0.0f;
                if( c.g < 0.0f )
                    c.g = 0.0f;
                if( c.b < 0.0f )
                    c.b = 0.0f;

                this->setPixel( x, y, &c );
            }
        }
    }

};



