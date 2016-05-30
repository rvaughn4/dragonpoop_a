
/*
*/

#include "tictactoe_menu_gui.h"
#include "tictactoe_menu_newgame.h"

namespace dp
{

    //ctor
    tictactoe_menu_gui::tictactoe_menu_gui( void ) : dpgui_window( 0, 0, 500, 600, "Tic Tac Toe", "A game to demonstrate the GUI system.", 50 )
    {
        dpgui_attribs a;

        this->getAttributes( &a );

        a.bIsCenter = 1;

        this->setAttributes( &a );
    }

    //dtor
    tictactoe_menu_gui::~tictactoe_menu_gui( void )
    {

    }

    //override to handle gui start
    bool tictactoe_menu_gui::onGuiStart( dpgui_writelock *tl )
    {
        dpgui *g;

        if( !this->dpgui_window::onGuiStart( tl ) )
            return 0;

        g = new tictactoe_menu_newgame( 0, 200, 400, 70, this );
        this->addGui( &g, 1 );

        return 1;
    }

}







