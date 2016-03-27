
/*

*/

#ifndef dpbitmap_png_bitmap_h
#define dpbitmap_png_bitmap_h

#include "../dpbitmap_compressed/dpbitmap_compressed.h"
#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"

namespace dp
{

    class dpbuffer_dynamic;
    class dpbitmap_png;

    class dpbitmap_png_bitmap : public dpbitmap_compressed
    {

    private:

        dpbitmap_png *png;

    protected:

        //uncompress image and store in bitmap
        virtual bool uncompress( dpbitmap *b );
        //compress image and overrwrite previous data
        virtual bool compress( dpbitmap *b );

    public:

        //ctor
        dpbitmap_png_bitmap( int w, int h );
        //ctor
        dpbitmap_png_bitmap( dpbuffer *b );
        //dtor
        virtual ~dpbitmap_png_bitmap( void );
        //returns width
        virtual int getWidth( void );
        //returns height
        virtual int getHeight( void );
        //get file header
        virtual bool getFileHeader( dpbuffer_static *b );
        //get bitmap header
        virtual bool getBitmapHeader( dpbuffer_static *b );
        //get pixel data
        virtual bool getPixelData( dpbuffer_static *b );
        //get extra data
        virtual bool getExtraData( dpbuffer_static *b );

    };

};

#endif





