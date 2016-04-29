
/*
*/

#include "dpgui_window.h"
#include "dpgui_window_title.h"
#include "dpgui_window_minimize_button.h"

namespace dp
{

    //ctor
    dpgui_window::dpgui_window( int x, int y, unsigned int w, unsigned int h, const char *ctitle, const char *ctxt ) : dpgui( x, y, w, h, ctxt )
    {
        this->setFloating( 1 );
        this->setCentered( 1 );
        this->stitle.assign( ctitle );
    }

    //dtor
    dpgui_window::~dpgui_window( void )
    {

    }

    //render first pass background image
    void dpgui_window::renderBackgroundPass0( dpbitmap *bm )
    {
        dpbitmap_color c;
        c.r = c.g = c.b = 0.65f;
        c.a = 0.75f;
        bm->fill( &c );
    }

    //render first pass background image
    void dpgui_window::renderBackgroundPass1( dpbitmap *bm )
    {
        bm->buttonize( 5, 0.5f, 0 );
    }

    //override to handle gui start
    bool dpgui_window::onGuiStart( dpgui_writelock *tl )
    {
        dpgui *t;
        unsigned int w, h;

        if( !this->dpgui::onGuiStart( tl ) )
            return 0;

        this->getDimensions( &w, &h );
        t = new dpgui_window_title( 0, -25, w, 30, this->stitle.c_str(), this );
        this->addGui( &t, 1 );

        return 1;
    }

}








