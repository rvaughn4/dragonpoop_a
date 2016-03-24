
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





