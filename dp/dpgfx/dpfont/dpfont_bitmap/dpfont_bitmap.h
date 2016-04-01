
/*

*/

#ifndef dpfont_bitmap_h
#define dpfont_bitmap_h

#include "../dpfont/dpfont.h"
#include "../../dpbitmap/dpbitmap_uncompressed/dpbitmap_uncompressed.h"

namespace dp
{

    class dpfont_bitmap : public dpbitmap_uncompressed
    {

    private:

        FT_Library lb;
        FT_Face fc;

    protected:

        //ctor
        dpfont_bitmap( dpbuffer *b );
        //return default red mask
        virtual uint32_t getRedMask( void );
        //return default green mask
        virtual uint32_t getGreenMask( void );
        //return default blue mask
        virtual uint32_t getBlueMask( void );
        //return default alpha mask
        virtual uint32_t getAlphaMask( void );

    public:

        //ctor
        dpfont_bitmap( FT_Library *lb, FT_Face *fc );
        //dtor
        virtual ~dpfont_bitmap( void );
        //returns width
        virtual int getWidth( void );
        //returns height
        virtual int getHeight( void );
        //returns true if upside down, also gets height
        virtual bool isUpsideDown( unsigned int *h );
        //returns bits per pixel
        virtual int getBits( void );
        //returns scan line length
        virtual unsigned int getScanSize( void );
        //get pixel data
        virtual bool getPixelData( dpbuffer_static *b );

    };

};

#endif




