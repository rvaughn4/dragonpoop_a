
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

        return this->b;
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

};




