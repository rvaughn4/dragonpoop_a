/*

*/

#ifndef tictactoe_menu_h
#define tictactoe_menu_h

#include "../../../dpgfx/dpscene/dpscene.h"

namespace dp
{

    class tictactoe_menu : public dpscene
    {

    private:

    protected:

        //override to handle scene start
        virtual bool onSceneStart( dpscene_writelock *sl );
        //override to handle scene stop
        virtual bool onSceneStop( dpscene_writelock *sl );
        //override to handle scene run
        virtual bool onSceneRun( dpscene_writelock *sl );
        //generate root gui
        virtual dpgui *genRootGui( dpscene_writelock *sl );

    public:

        //ctor
        tictactoe_menu( void );
        //dtor
        virtual ~tictactoe_menu( void );

    };

};

#endif


