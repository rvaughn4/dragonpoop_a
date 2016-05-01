
/*
*/

#include "dpgui_window_title.h"
#include "dpgui_window_minimize_button.h"
#include "dpgui_window_close_button.h"
#include "dpgui_window_zoom_in_button.h"
#include "dpgui_window_zoom_out_button.h"

namespace dp
{

    //ctor
    dpgui_window_title::dpgui_window_title( int x, int y, unsigned int w, unsigned int h, const char *ctxt, dpgui *pgui ) : dpgui( x, y, w, h, ctxt )
    {
        float bw;
        dpbitmap_color c;

        this->pgui = (dpgui_ref *)this->g.getRef( pgui );
        if( h < 4 )
            h = 4;
        this->h = h;

        bw = 5.0f * 2.0f;
        if( bw > w )
            bw = w;
        if( bw > h )
            bw = h;
        bw = bw / 2.0f;

        this->setBorderWidth( bw );

        c.r = 0.75f;
        c.g = 0.75f;
        c.b = 0.75f;
        c.a = 0.5f;
        this->setBgColor( &c );

        c.r = 0.0f;
        c.g = 0.0f;
        c.b = 0.0f;
        c.a = 1.0f;
        this->setFontColor( &c );

        this->setHorizFill( 1 );
    }

    //dtor
    dpgui_window_title::~dpgui_window_title( void )
    {

    }

    //override to handle gui start
    bool dpgui_window_title::onGuiStart( dpgui_writelock *tl )
    {
        dpgui *t;
        float x;

        if( !this->dpgui::onGuiStart( tl ) )
            return 0;

        x = 4;
        t = new dpgui_window_close_button( x, 4, this->h - 5, this->h - 7, this->pgui );
        this->addGui( &t, 1 );

        x += 1 + this->h;
        t = new dpgui_window_minimize_button( x, 4, this->h - 5, this->h - 7, this->pgui );
        this->addGui( &t, 1 );

        x += 1 + this->h;
        t = new dpgui_window_zoom_out_button( x, 4, this->h - 5, this->h - 7, this->pgui );
        this->addGui( &t, 1 );

        x += 1 + this->h;
        t = new dpgui_window_zoom_in_button( x, 4, this->h - 5, this->h - 7, this->pgui );
        this->addGui( &t, 1 );

        return 1;
    }

}









