
/*
*/

#include "dpgui_window_close_button.h"
#include "../../dpgui/dpgui_ref.h"
#include "../../dpgui/dpgui_writelock.h"

namespace dp
{

    //ctor
    dpgui_window_close_button::dpgui_window_close_button( int x, int y, unsigned int w, unsigned int h, dpgui_ref *pgui ) : dpgui_button( x, y, w, h, ".X" )
    {
        dpgui_attribs a;

        this->pgui = (dpgui_ref *)this->g.getRef( pgui );

        this->getAttributes( &a );

        a.align = dpgui_alignment_right;
        a.fnt_size = 25;

        a.bg_clr.r = 1.0f;
        a.bg_clr.g = 0.0f;
        a.bg_clr.b = 0.0f;
        a.bg_clr.a = 0.5f;

        this->setAttributes( &a );
    }

    //dtor
    dpgui_window_close_button::~dpgui_window_close_button( void )
    {

    }

    //override to handle left clicks
    void dpgui_window_close_button::onLeftClick( dpinput_event_mouse *e )
    {
        dpgui_writelock *l;
        dpshared_guard g;

        l = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->pgui, 1000 );
        if( !l )
            return;

        l->stop();
    }

}







