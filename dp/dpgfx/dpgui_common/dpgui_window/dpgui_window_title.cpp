
/*
*/

#include "dpgui_window_title.h"
#include "dpgui_window_minimize_button.h"

namespace dp
{

    //ctor
    dpgui_window_title::dpgui_window_title( int x, int y, unsigned int w, unsigned int h, const char *ctxt, dpgui *pgui ) : dpgui( x, y, w, h, ctxt )
    {
        this->pgui = (dpgui_ref *)this->g.getRef( pgui );
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

    //override to handle gui start
    bool dpgui_window_title::onGuiStart( dpgui_writelock *tl )
    {
        dpgui *t;

        if( !this->dpgui::onGuiStart( tl ) )
            return 0;

        t = new dpgui_window_minimize_button( -100, 0, 50, 50, this->pgui );
        this->addGui( &t, 1 );

        return 1;
    }

}









