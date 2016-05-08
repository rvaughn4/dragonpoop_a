
/*
*/

#include "dpgui_taskman.h"

namespace dp
{

    //ctor
    dpgui_taskman::dpgui_taskman( void ) : dpgui_window( 50, 50, 300, 800, "Tasks", "uhoh", 50 )
    {

    }

    //dtor
    dpgui_taskman::~dpgui_taskman( void )
    {

    }
/*
    //override to handle gui start
    bool dpgui_taskman::onGuiStart( dpgui_writelock *tl )
    {
        if( !this->dpgui_window::onGuiStart( tl ) )
            return 0;

        return 1;
    }

    //override to handle gui ran
    bool dpgui_taskman::onGuiRun( dpgui_writelock *tl )
    {
        if( !this->dpgui_window::onGuiRun( tl ) )
            return 0;

        return 1;
    }
*/
}








