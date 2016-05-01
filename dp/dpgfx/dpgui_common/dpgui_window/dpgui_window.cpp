
/*
*/

#include "dpgui_window.h"
#include "dpgui_window_title.h"
#include "dpgui_window_minimize_button.h"

namespace dp
{

    //ctor
    dpgui_window::dpgui_window( int x, int y, unsigned int w, unsigned int h, const char *ctitle, const char *ctxt, unsigned int title_size ) : dpgui( x, y, w, h, ctxt )
    {
        dpbitmap_color c;
        float bw;

        this->setFloating( 1 );
        this->stitle.assign( ctitle );
        this->title_sz = title_size;

        bw = 5.0f * 2.0f;
        if( bw > w )
            bw = w;
        if( bw > h )
            bw = h;
        bw = bw / 2.0f;

        this->setBorderWidth( bw );

        c.r = 1.0f;
        c.g = 1.0f;
        c.b = 1.0f;
        c.a = 0.5f;
        this->setBgColor( &c );

        c.r = 0.0f;
        c.g = 0.0f;
        c.b = 0.0f;
        c.a = 1.0f;
        this->setFontColor( &c );
    }

    //dtor
    dpgui_window::~dpgui_window( void )
    {

    }

    //override to handle gui start
    bool dpgui_window::onGuiStart( dpgui_writelock *tl )
    {
        dpgui *t;
        unsigned int w, h;

        if( !this->dpgui::onGuiStart( tl ) )
            return 0;

        this->getDimensions( &w, &h );
        t = new dpgui_window_title( 0, -this->title_sz + 3, w, this->title_sz, this->stitle.c_str(), this );
        this->addGui( &t, 1 );

        return 1;
    }

}








