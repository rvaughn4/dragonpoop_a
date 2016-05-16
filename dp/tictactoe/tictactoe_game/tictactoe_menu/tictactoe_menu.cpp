/*

*/

#include "tictactoe_menu.h"

namespace dp
{

    //ctor
    tictactoe_menu::tictactoe_menu( void ) : dpscene( )
    {

    }

    //dtor
    tictactoe_menu::~tictactoe_menu( void )
    {

    }

    //override to handle scene start
    bool tictactoe_menu::onSceneStart( dpscene_writelock *sl )
    {
        if( !this->dpscene::onSceneStart( sl ) )
            return 0;

        return 1;
    }

    //override to handle scene stop
    bool tictactoe_menu::onSceneStop( dpscene_writelock *sl )
    {
        if( !this->dpscene::onSceneStop( sl ) )
            return 0;

        return 1;
    }

    //override to handle scene run
    bool tictactoe_menu::onSceneRun( dpscene_writelock *sl )
    {
        if( !this->dpscene::onSceneRun( sl ) )
            return 0;

        return 1;
    }

    //generate root gui
    dpgui *tictactoe_menu::genRootGui( dpscene_writelock *sl )
    {
        return this->dpscene::genRootGui( sl );
    }

};



