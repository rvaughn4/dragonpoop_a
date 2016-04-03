
/*

*/

#ifndef dpfont_filter_size_h
#define dpfont_filter_size_h

#include "../dpfont_filter/dpfont_filter.h"

namespace dp
{

    class dpfont_filter_size : public dpfont_filter
    {

    private:

    protected:

    public:

        //ctor
        dpfont_filter_size( void );
        //dtor
        virtual ~dpfont_filter_size( void );
        //run filter
        virtual unsigned int run( char *b, unsigned int sz, dpbitmap_position *pos_in, dpbitmap *dest_bmp, dpfont *fnt );

    };

};

#endif


