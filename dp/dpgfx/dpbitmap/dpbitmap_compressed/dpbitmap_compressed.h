
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
        //copy bitmap
        virtual void copy( dpbitmap *b );
        //load buffer from buffer
        virtual bool load( dpbuffer *b );
        //load buffer from file
        virtual bool load( const char *fname );
        //save buffer to file
        virtual bool save( const char *fname );
        //save buffer to buffer
        virtual bool save( dpbuffer *b );

    };

};

#endif



