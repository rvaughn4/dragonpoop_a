
/*
*/

#include "tictactoe_menu_newgame.h"
#include "../../../../dpgfx/dpgui/dpgui_ref.h"
#include "../../../../dpgfx/dpgui/dpgui_writelock.h"

namespace dp
{

    //ctor
    tictactoe_menu_newgame::tictactoe_menu_newgame( int x, int y, unsigned int w, unsigned int h, dpgui *pgui ) : dpgui_button( x, y, w, h, "New Game" )
    {
        dpgui_attribs a;

        this->pgui = (dpgui_ref *)this->g.getRef( pgui );

        this->getAttributes( &a );

        a.align = dpgui_alignment_center;
        a.fnt_size = 25;

        a.bg_clr.r = 1.0f;
        a.bg_clr.g = 0.0f;
        a.bg_clr.b = 0.0f;
        a.bg_clr.a = 0.5f;

        this->setAttributes( &a );
    }

    //dtor
    tictactoe_menu_newgame::~tictactoe_menu_newgame( void )
    {

    }

    //override to handle left clicks
    void tictactoe_menu_newgame::onLeftClick( dpinput_event_mouse *e )
    {
        dpgui_writelock *l;
        dpshared_guard g;

        l = (dpgui_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->pgui, 1000 );
        if( !l )
            return;

        l->stop();
    }

}








