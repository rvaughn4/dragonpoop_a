
/*

*/

#ifndef dpbitmap_32bit_uncompressed_h
#define dpbitmap_32bit_uncompressed_h

#include "../dpbitmap_uncompressed/dpbitmap_uncompressed.h"

namespace dp
{

    class dpbitmap_32bit_uncompressed : public dpbitmap_uncompressed
    {

    private:

    protected:

        //write color to pointer
        virtual bool writeColor( dpbitmap_color *c, dpbuffer *b );
        //read color from pointer
        virtual bool readColor( dpbitmap_color *c, dpbuffer *b );

    public:

        //ctor
        dpbitmap_32bit_uncompressed( int w, int h );
        //ctor
        dpbitmap_32bit_uncompressed( dpbuffer *b );
        //dtor
        virtual ~dpbitmap_32bit_uncompressed( void );
        //returns bits per pixel
        virtual int getBits( void );
        //returns scan line length
        virtual unsigned int getScanSize( void );

    };

};

#endif




