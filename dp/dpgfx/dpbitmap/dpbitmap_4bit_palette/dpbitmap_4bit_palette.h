
/*

*/

#ifndef dpbitmap_4bit_palette_h
#define dpbitmap_4bit_palette_h

#include "../dpbitmap_uncompressed_palette/dpbitmap_uncompressed_palette.h"

namespace dp
{

    class dpbitmap_4bit_palette : public dpbitmap_uncompressed_palette
    {

    private:

    protected:

    public:

        //ctor
        dpbitmap_4bit_palette( int w, int h );
        //ctor
        dpbitmap_4bit_palette( dpbuffer *b );
        //dtor
        virtual ~dpbitmap_4bit_palette( void );
        //returns bits per pixel
        virtual int getBits( void );

    };

};

#endif







