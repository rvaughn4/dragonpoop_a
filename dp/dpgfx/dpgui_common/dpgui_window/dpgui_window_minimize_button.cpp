
/*
*/

#include "dpgui_window_minimize_button.h"
#include "../../dpgui/dpgui_ref.h"
#include "../../dpgui/dpgui_writelock.h"

namespace dp
{

    //ctor
    dpgui_window_minimize_button::dpgui_window_minimize_button( int x, int y, unsigned int w, unsigned int h, dpgui_ref *pgui ) : dpgui_button( x, y, w, h, "___" )
    {
        dpgui_attribs a;

        this->pgui = (dpgui_ref *)this->g.getRef( pgui );

        this->getAttributes( &a );

        a.align = dpgui_alignment_right;
        a.fnt_size = 15;

        a.bg_clr.r = 0.7f;
        a.bg_clr.g = 0.7f;
        a.bg_clr.b = 0.7f;
        a.bg_clr.a = 0.5f;

        this->setAttributes( &a );
    }

    //dtor
    dpgui_window_minimize_button::~dpgui_window_minimize_button( void )
    {

    }

    //override to handle left clicks
    void dpgui_window_minimize_button::onLeftClick( dpinput_event_mouse *e )
    {
        dpgui_writelock *l;
        dpshared_guard g;
        dpgui_attribs a;

        l = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->pgui, 1000 );
        if( !l )
            return;

        l->getAttributes( &a );
        a.bIsMin = 1;
        l->setAttributes( &a );
        l->update();

        this->dpgui_button::onLeftClick( e );
    }

}






