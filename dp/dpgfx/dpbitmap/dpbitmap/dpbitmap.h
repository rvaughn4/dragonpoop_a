
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
        virtual void copy( dpbitmap *b ) = 0;

    };

};

#endif


