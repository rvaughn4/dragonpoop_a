
/*

*/

#ifndef dpbitmap_compressed_h
#define dpbitmap_compressed_h

#include "../dpbitmap/dpbitmap.h"

namespace dp
{

    class dpbitmap_compressed : public dpbitmap
    {

    private:

        dpbitmap *b;

    protected:

        //ctor
        dpbitmap_compressed( int w, int h );
        //ctor
        dpbitmap_compressed( dpbuffer *b );
        //uncompress image and store in bitmap
        virtual bool uncompress( dpbitmap *b ) = 0;
        //compress image and overrwrite previous data
        virtual bool compress( dpbitmap *b ) = 0;

    public:

        //dtor
        virtual ~dpbitmap_compressed( void );
        //set pixel color
        virtual bool setPixel( int x, int y, dpbitmap_color *c );
        //get pixel color
        virtual bool getPixel( int x, int y, dpbitmap_color *c );
        //returns width
        virtual int getWidth( void ) = 0;
        //returns height
        virtual int getHeight( void ) = 0;
        //returns uncompressed bitmap, if not uncompressed already, uncompresses image and makes the uncompressed bitmap
        virtual dpbitmap *getUncompressed( void );
        //load buffer from buffer
        virtual bool load( dpbuffer *b );
        //load buffer from file
        virtual bool load( const char *fname );
        //save buffer to file
        virtual bool save( const char *fname );
        //save buffer to buffer
        virtual bool save( dpbuffer *b );
        //copy bitmap
        virtual void copy( dpbitmap *b );
        //copy bitmap into position
        virtual void copyInto( dpbitmap *b, dpbitmap_position *p_dest );
        //copy bitmap into rect
        virtual void copyInto( dpbitmap *b, dpbitmap_rectangle *p_dest );
        //copy bitmap from position
        virtual void copyFrom( dpbitmap *b, dpbitmap_position *p_src );
        //copy bitmap from rect
        virtual void copyFrom( dpbitmap *b, dpbitmap_rectangle *p_src );
        //copy bitmap from position into position
        virtual void copy( dpbitmap *b, dpbitmap_position *p_src, dpbitmap_position *p_dest );
        //copy bitmap from rect into position
        virtual void copy( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_position *p_dest );
        //copy bitmap from position into rect
        virtual void copy( dpbitmap *b, dpbitmap_position *p_src, dpbitmap_rectangle *p_dest );
        //copy bitmap from rect into rect
        virtual void copy( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_rectangle *p_dest );
        //copy without stretching to position
        virtual void copyNoStretch( dpbitmap *b, dpbitmap_position *p_dest );
        //copy without stretching to position
        virtual void copyNoStretch( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_position *p_dest );
        //set color mask
        virtual void setColorMask( dpbitmap_color *c );
        //set color clamp
        virtual void setColorClamp( dpbitmap_color *c );
        //set transparency mode
        virtual void setTransparencyMode( int m );
        //draw colored rectangle
        virtual void fill( dpbitmap_color *c );
        //draw colored rectangle
        virtual void fill( dpbitmap_color *c, dpbitmap_rectangle *rc );
        //clear rectanlge
        virtual void clear( void );
        //clear rectanlge
        virtual void clear( dpbitmap_rectangle *rc );

    };

};

#endif



