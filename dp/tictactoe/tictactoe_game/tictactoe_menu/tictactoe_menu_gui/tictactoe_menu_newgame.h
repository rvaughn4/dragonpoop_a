
/*
*/

#ifndef tictactoe_menu_newgame_h
#define tictactoe_menu_newgame_h

#include "../../../../dpgfx/dpgui_common/dpgui_button/dpgui_button.h"

namespace dp
{

    class dpgui_ref;

    class tictactoe_menu_newgame : public dpgui_button
    {

    private:

        dpgui_ref *pgui;
        dpshared_guard g;

    protected:

        //override to handle left clicks
        virtual void onLeftClick( dpinput_event_mouse *e );

    public:

        //ctor
        tictactoe_menu_newgame( int x, int y, unsigned int w, unsigned int h, dpgui *pgui );
        //dtor
        virtual ~tictactoe_menu_newgame( void );

    };

}

#endif








