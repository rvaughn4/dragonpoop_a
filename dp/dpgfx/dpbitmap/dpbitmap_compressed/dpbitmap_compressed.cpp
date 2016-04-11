
/*

*/

#include "dpbitmap_compressed.h"
#include "../dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"

namespace dp
{

    //ctor
    dpbitmap_compressed::dpbitmap_compressed( int w, int h ) : dpbitmap()
    {
        this->b = 0;
    }

    //ctor
    dpbitmap_compressed::dpbitmap_compressed( dpbuffer *b ) : dpbitmap( b )
    {
        this->b = 0;
    }

    //dtor
    dpbitmap_compressed::~dpbitmap_compressed( void )
    {
        if( this->b )
            delete this->b;
    }

    //set pixel color
    bool dpbitmap_compressed::setPixel( int x, int y, dpbitmap_color *c )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return 0;

        return nb->setPixel( x, y, c );
    }

    //get pixel color
    bool dpbitmap_compressed::getPixel( int x, int y, dpbitmap_color *c )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return 0;

        return nb->getPixel( x, y, c );
    }

    //returns uncompressed bitmap, if not uncompressed already, uncompresses image and makes the uncompressed bitmap
    dpbitmap *dpbitmap_compressed::getUncompressed( void )
    {
        dpbitmap *nb;
        unsigned int w, h;
        dpbitmap_color c;

        if( !this->b )
        {
            w = this->getWidth();
            h = this->getHeight();

            nb = new dpbitmap_32bit_uncompressed( w, h );
            if( !nb )
                return 0;
            if( this->uncompress( nb ) )
            {
                this->b = nb;
                return nb;
            }
            delete nb;
            return 0;
        }

        this->getColorClamp( &c );
        this->b->setColorClamp( &c );
        this->getColorMask( &c );
        this->b->setColorMask( &c );
        this->b->setTransparencyMode( this->getTransparencyMode() );

        return this->b;
    }

    //load buffer from buffer
    bool dpbitmap_compressed::load( dpbuffer *b )
    {
        if( this->b )
            delete this->b;
        this->b = 0;
        return dpbitmap::load( b );
    }

    //load buffer from file
    bool dpbitmap_compressed::load( const char *fname )
    {
        if( this->b )
            delete this->b;
        this->b = 0;
        return dpbitmap::load( fname );
    }

    //save buffer to file
    bool dpbitmap_compressed::save( const char *fname )
    {
        if( this->b && !this->compress( this->b ) )
            return 0;
        return this->dpbitmap::save( fname );
    }

    //save buffer to buffer
    bool dpbitmap_compressed::save( dpbuffer *b )
    {
        if( this->b && !this->compress( this->b ) )
            return 0;
        return this->dpbitmap::save( b );
    }

    //copy bitmap
    void dpbitmap_compressed::copy( dpbitmap *b )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copy( b );
    }

    //copy bitmap into position
    void dpbitmap_compressed::copyInto( dpbitmap *b, dpbitmap_position *p_dest )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copyInto( b, p_dest );
    }

    //copy bitmap into rect
    void dpbitmap_compressed::copyInto( dpbitmap *b, dpbitmap_rectangle *p_dest )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copyInto( b, p_dest );
    }

    //copy bitmap from position
    void dpbitmap_compressed::copyFrom( dpbitmap *b, dpbitmap_position *p_src )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copyFrom( b, p_src );
    }

    //copy bitmap from rect
    void dpbitmap_compressed::copyFrom( dpbitmap *b, dpbitmap_rectangle *p_src )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copyFrom( b, p_src );
    }

    //copy bitmap from position into position
    void dpbitmap_compressed::copy( dpbitmap *b, dpbitmap_position *p_src, dpbitmap_position *p_dest )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copy( b, p_src, p_dest );
    }

    //copy bitmap from rect into position
    void dpbitmap_compressed::copy( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_position *p_dest )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copy( b, p_src, p_dest );
    }

    //copy bitmap from position into rect
    void dpbitmap_compressed::copy( dpbitmap *b, dpbitmap_position *p_src, dpbitmap_rectangle *p_dest )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copy( b, p_src, p_dest );
    }

    //copy bitmap from rect into rect
    void dpbitmap_compressed::copy( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_rectangle *p_dest )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copy( b, p_src, p_dest );
    }

    //copy without stretching to position
    void dpbitmap_compressed::copyNoStretch( dpbitmap *b, dpbitmap_position *p_dest )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copyNoStretch( b, p_dest );
    }

    //copy without stretching to position
    void dpbitmap_compressed::copyNoStretch( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_position *p_dest )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->copyNoStretch( b, p_src, p_dest );
    }

    //set color mask
    void dpbitmap_compressed::setColorMask( dpbitmap_color *c )
    {
        this->dpbitmap::setColorMask( c );
        if( this->b )
            this->b->setColorMask( c );
    }

    //set color clamp
    void dpbitmap_compressed::setColorClamp( dpbitmap_color *c )
    {
        this->dpbitmap::setColorClamp( c );
        if( this->b )
            this->b->setColorClamp( c );
    }

    //set transparency mode
    void dpbitmap_compressed::setTransparencyMode( int m )
    {
        this->dpbitmap::setTransparencyMode( m );
        if( this->b )
            this->b->setTransparencyMode( m );
    }

    //draw colored rectangle
    void dpbitmap_compressed::fill( dpbitmap_color *c )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->fill( c );
    }

    //draw colored rectangle
    void dpbitmap_compressed::fill( dpbitmap_color *c, dpbitmap_rectangle *rc )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->fill( c, rc );
    }

    //clear rectanlge
    void dpbitmap_compressed::clear( void )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->clear();
    }

    //clear rectanlge
    void dpbitmap_compressed::clear( dpbitmap_rectangle *rc )
    {
        dpbitmap *nb;

        nb = this->getUncompressed();
        if( !nb )
            return;

        nb->clear( rc );
    }

};




