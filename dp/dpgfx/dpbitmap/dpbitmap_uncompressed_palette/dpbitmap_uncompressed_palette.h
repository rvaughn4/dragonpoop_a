
/*

*/

#ifndef dpbitmap_uncompressed_palette_h
#define dpbitmap_uncompressed_palette_h

#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"

namespace dp
{

    class dpbitmap_uncompressed_palette : public dpbitmap_uncompressed
    {

    private:

    protected:

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
        dpbitmap_uncompressed_palette( int w, int h, int bits );
        //ctor
        dpbitmap_uncompressed_palette( dpbuffer *b );
        //dtor
        virtual ~dpbitmap_uncompressed_palette( void );
        //returns bits per pixel
        virtual int getBits( void ) = 0;
        //returns scan line length
        virtual unsigned int getScanSize( void );
        //set pixel color
        virtual bool setPixel( int x, int y, dpbitmap_color *c );
        //get pixel color
        virtual bool getPixel( int x, int y, dpbitmap_color *c );
        //get palette data
        virtual bool getPaletteData( dpbuffer_static *b );
        //find closest color in palette
        virtual bool findColor( uint32_t *i, dpbitmap_color *c );
        //convert palette index to color
        virtual bool getPaletteColor( uint32_t i, dpbitmap_color *c );
        //set palette color
        virtual bool setPaletteColor( uint32_t i, dpbitmap_color *c );
    };

};

#endif






