
/*

*/

#ifndef dpbuffer_compress_h
#define dpbuffer_compress_h

namespace dp
{

    class dpbuffer;

    class dpbuffer_compress
    {

    private:

    protected:

        //ctor
        dpbuffer_compress( void );

    public:

        //dtor
        virtual ~dpbuffer_compress( void );
        //compress source buffer and output into dest buffer
        virtual bool compress( dpbuffer *src, dpbuffer *dest ) = 0;
        //decompress source buffer and output into dest buffer
        virtual bool decompress( dpbuffer *src, dpbuffer *dest ) = 0;

    };

};

#endif

