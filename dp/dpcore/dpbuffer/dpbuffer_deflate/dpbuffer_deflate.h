
/*

*/

#ifndef dpbuffer_deflate_h
#define dpbuffer_deflate_h

#include "../dpbuffer_compress/dpbuffer_compress.h"
#include <stdint.h>

namespace dp
{

    class dpbuffer;

    #define dpbuffer_deflate_no_compress 0
    #define dpbuffer_deflate_static_huffman 1
    #define dpbuffer_deflate_dynamic_huffman 2

    class dpbuffer_deflate : public dpbuffer_compress
    {

    private:

        //read next section
        bool readSection( dpbuffer *src, dpbuffer *dest );
        //write next section
        bool writeSection( dpbuffer *src, dpbuffer *dest, unsigned int len );
        //test next section
        uint8_t testSection( dpbuffer *src, unsigned int len );
        //read uncompressed section
        bool readUncompressed( dpbuffer *src, dpbuffer *dest );
        //write uncompressed section
        bool writeUncompressed( dpbuffer *src, dpbuffer *dest, unsigned int len );

    protected:

    public:

        //ctor
        dpbuffer_deflate( void );
        //dtor
        virtual ~dpbuffer_deflate( void );
        //compress source buffer and output into dest buffer
        virtual bool compress( dpbuffer *src, dpbuffer *dest );
        //decompress source buffer and output into dest buffer
        virtual bool decompress( dpbuffer *src, dpbuffer *dest );

    };

};

#endif


