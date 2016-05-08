
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
        float bw;
        dpgui_attribs a;

        this->stitle.assign( ctitle );
        this->title_sz = title_size;

        this->getAttributes( &a );

        bw = 5.0f * 2.0f;
        if( bw > w )
            bw = w;
        if( bw > h )
            bw = h;
        bw = bw / 2.0f;
        a.border_size = bw;
        a.bIsFloat = 1;
        a.fnt_size = 12;

        a.bg_clr.r = 1.0f;
        a.bg_clr.g = 1.0f;
        a.bg_clr.b = 1.0f;
        a.bg_clr.a = 0.5f;

        a.fnt_clr.r = 0.0f;
        a.fnt_clr.g = 0.0f;
        a.fnt_clr.b = 0.0f;
        a.fnt_clr.a = 1.0f;

        this->setAttributes( &a );
    }

    //dtor
    dpgui_window::~dpgui_window( void )
    {

    }

    //override to handle gui start
    bool dpgui_window::onGuiStart( dpgui_writelock *tl )
    {
        dpgui *t;
        dpgui_attribs a;

        if( !this->dpgui::onGuiStart( tl ) )
            return 0;

        this->getAttributes( &a );
        t = new dpgui_window_title( 0, -this->title_sz + 3, a.rc.w, this->title_sz, this->stitle.c_str(), this );
        this->addGui( &t, 1 );

        return 1;
    }

}








