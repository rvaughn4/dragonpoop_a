
/*

*/

#ifndef dpbitmap_8bit_palette_h
#define dpbitmap_8bit_palette_h

#include "../dpbitmap_uncompressed_palette/dpbitmap_uncompressed_palette.h"

namespace dp
{

    class dpbitmap_8bit_palette : public dpbitmap_uncompressed_palette
    {

    private:

    protected:

    public:

        //ctor
        dpbitmap_8bit_palette( int w, int h );
        //ctor
        dpbitmap_8bit_palette( dpbuffer *b );
        //dtor
        virtual ~dpbitmap_8bit_palette( void );
        //returns bits per pixel
        virtual int getBits( void );

    };

};

#endif







