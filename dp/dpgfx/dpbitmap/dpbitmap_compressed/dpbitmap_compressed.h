
/*

*/

#ifndef dpbitmap_compressed_h
#define dpbitmap_compressed_h

#include "../bpbitmap.h"

namespace dp
{

    class dpbitmap_compressed : public dpbitmap
    {

    private:

        dpbuffer *b;

    protected:

        //ctor
        dpbitmap_compressed( void );
        //ctor
        dpbitmap_compressed( dpbuffer *b );
        //uncompress image and store in bitmap

        //compress image and overrwrite previous data

    public:

        //dtor
        virtual ~dpbitmap_compressed( void );
        //set pixel color
        virtual bool setPixel( int x, int y, dpbitmap_color *c );
        //get pixel color
        virtual bool getPixel( int x, int y, dpbitmap_color *c );
        //returns width
        virtual int getWidth( void );
        //returns height
        virtual int getHeight( void );
        //returns uncompressed bitmap, if not uncompressed already, uncompresses image and makes the uncompressed bitmap
        virtual dpbitmap *getUncompressed( void );
        //copy bitmap
        virtual void copy( dpbitmap *b );

    };

};

#endif



