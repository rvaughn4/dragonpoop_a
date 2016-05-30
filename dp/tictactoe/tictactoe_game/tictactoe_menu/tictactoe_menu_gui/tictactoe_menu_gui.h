
/*
*/

#ifndef dploader_tictactoe_menu_gui_h
#define dploader_tictactoe_menu_gui_h

#include "../../../../dpgfx/dpgui_common/dpgui_window/dpgui_window.h"

namespace dp
{

    class tictactoe_menu_gui : public dpgui_window
    {

    private:

    protected:

        //override to handle gui start
        virtual bool onGuiStart( dpgui_writelock *tl );

    public:

        //ctor
        tictactoe_menu_gui( void );
        //dtor
        virtual ~tictactoe_menu_gui( void );

    };

}

#endif






