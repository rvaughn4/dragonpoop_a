
/*
*/

#include "dpgui_window_title.h"

namespace dp
{

    //ctor
    dpgui_window_title::dpgui_window_title( int x, int y, unsigned int w, unsigned int h, const char *ctxt ) : dpgui( x, y, w, h, ctxt )
    {

    }

    //dtor
    dpgui_window_title::~dpgui_window_title( void )
    {

    }

    //render first pass background image
    void dpgui_window_title::renderBackgroundPass0( dpbitmap *bm )
    {
        dpbitmap_color c;
        c.r = c.g = c.b = 0.85f;
        c.a = 0.75f;
        bm->fill( &c );
    }

    //render first pass background image
    void dpgui_window_title::renderBackgroundPass1( dpbitmap *bm )
    {
        bm->buttonize( 5, 0.5f, 0 );
    }

}









