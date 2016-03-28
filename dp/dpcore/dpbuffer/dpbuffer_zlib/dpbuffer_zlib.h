
/*

*/

#ifndef dpbuffer_zlib_h
#define dpbuffer_zlib_h

#include "../dpbuffer_compress/dpbuffer_compress.h"

namespace dp
{

    class dpbuffer_zlib : public dpbuffer_compress
    {

    private:

    protected:

    public:

        //ctor
        dpbuffer_zlib( void );
        //dtor
        virtual ~dpbuffer_zlib( void );
        //compress source buffer and output into dest buffer
        virtual bool compress( dpbuffer *src, dpbuffer *dest );
        //decompress source buffer and output into dest buffer
        virtual bool decompress( dpbuffer *src, dpbuffer *dest );

    };

};

#endif



