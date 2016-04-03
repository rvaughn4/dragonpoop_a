
/*

*/

#ifndef dpfont_filter_face_h
#define dpfont_filter_face_h

#include "../dpfont_filter/dpfont_filter.h"

namespace dp
{

    class dpfont_filter_face : public dpfont_filter
    {

    private:

    protected:

    public:

        //ctor
        dpfont_filter_face( void );
        //dtor
        virtual ~dpfont_filter_face( void );
        //run filter
        virtual unsigned int run( char *b, unsigned int sz, dpbitmap_position *pos_in, dpbitmap *dest_bmp, dpfont *fnt );

    };

};

#endif



