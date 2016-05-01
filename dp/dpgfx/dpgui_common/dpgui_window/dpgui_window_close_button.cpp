
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
        dpbitmap_color c;

        this->pgui = (dpgui_ref *)this->g.getRef( pgui );
        this->setAlignment( dpgui_alignment_right );
        this->setFontSize( 25 );

        c.r = 1.0f;
        c.g = 0.0f;
        c.b = 0.0f;
        c.a = 0.5f;
        this->setBgColor( &c );
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







