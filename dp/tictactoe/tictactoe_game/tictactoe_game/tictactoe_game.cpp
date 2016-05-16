
/*

*/

#include "tictactoe_game.h"
#include "../tictactoe_menu/tictactoe_menu.h"

namespace dp
{

    //ctor
    tictactoe_game::tictactoe_game( void )
    {
        dpscene *s;
        s = new tictactoe_menu();
        this->setFirstScene( &s );
    }

    //dtor
    tictactoe_game::~tictactoe_game( void )
    {

    }

};




