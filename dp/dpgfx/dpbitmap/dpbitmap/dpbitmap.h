
/*

*/

#ifndef dpbitmap_h
#define dpbitmap_h

#include "../../../dpcore/dpbuffer/dpbuffer_wrapper/dpbuffer_wrapper.h"
#include "../../../dpcore/dpbuffer/dpbuffer_dynamic/dpbuffer_dynamic.h"

namespace dp
{

    struct dpbitmap_color
    {
        float r, g, b, a;
    };

    struct dpbitmap_position
    {
        int32_t x, y;
    };

    struct dpbitmap_rectangle
    {
        union
        {
            dpbitmap_position p;
            struct
            {
                int32_t x, y;
            };
        };
        uint32_t w, h;
    };

    class dpbitmap : public dpbuffer_wrapper
    {

    private:

        dpbuffer_dynamic int_b;

    protected:

        //ctor
        dpbitmap( void );
        //ctor
        dpbitmap( dpbuffer *b );

    public:

        //dtor
        virtual ~dpbitmap( void );
        //set pixel color
        virtual bool setPixel( int x, int y, dpbitmap_color *c ) = 0;
        //get pixel color
        virtual bool getPixel( int x, int y, dpbitmap_color *c ) = 0;
        //returns width
        virtual int getWidth( void ) = 0;
        //returns height
        virtual int getHeight( void ) = 0;
        //copy bitmap
        virtual void copy( dpbitmap *b );
        //load buffer from buffer
        virtual bool load( dpbuffer *b );
        //load buffer from file
        virtual bool load( const char *fname );
        //save buffer to file
        virtual bool save( const char *fname );
        //save buffer to buffer
        virtual bool save( dpbuffer *b );
        //get pixel offset
        virtual void getPixelOffset( int *x, int *y );
        //copy bitmap into position
        virtual void copyInto( dpbitmap *b, dpbitmap_position *p_dest );
        //copy bitmap into rect
        virtual void copyInto( dpbitmap *b, dpbitmap_rectangle *p_dest );
        //copy bitmap from position
        virtual void copyFrom( dpbitmap *b, dpbitmap_position *p_src );
        //copy bitmap from rect
        virtual void copyFrom( dpbitmap *b, dpbitmap_rectangle *p_src );
        //copy bitmap from position into position
        virtual void copy( dpbitmap *b, dpbitmap_position *p_src, dpbitmap_position *p_dest );
        //copy bitmap from rect into position
        virtual void copy( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_position *p_dest );
        //copy bitmap from position into rect
        virtual void copy( dpbitmap *b, dpbitmap_position *p_src, dpbitmap_rectangle *p_dest );
        //copy bitmap from rect into rect
        virtual void copy( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_rectangle *p_dest );
        //copy without stretching to position
        virtual void copyNoStretch( dpbitmap *b, dpbitmap_position *p_dest );
        //copy without stretching to position
        virtual void copyNoStretch( dpbitmap *b, dpbitmap_rectangle *p_src, dpbitmap_position *p_dest );

    };

};

#endif


