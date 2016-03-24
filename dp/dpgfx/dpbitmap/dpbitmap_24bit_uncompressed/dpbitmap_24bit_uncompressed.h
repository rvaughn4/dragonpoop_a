
/*

*/

#ifndef dpbitmap_24bit_uncompressed_h
#define dpbitmap_24bit_uncompressed_h

#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"

namespace dp
{

    class dpbitmap_24bit_uncompressed : public dpbitmap_uncompressed
    {

    private:

    protected:

        //write color to pointer
        virtual bool writeColor( dpbitmap_color *c, dpbuffer *b );
        //read color from pointer
        virtual bool readColor( dpbitmap_color *c, dpbuffer *b );

    public:

        //ctor
        dpbitmap_24bit_uncompressed( int w, int h );
        //ctor
        dpbitmap_24bit_uncompressed( dpbuffer *b );
        //dtor
        virtual ~dpbitmap_24bit_uncompressed( void );
        //returns bits per pixel
        virtual int getBits( void );
        //returns scan line length
        virtual unsigned int getScanSize( void );

    };

};

#endif





