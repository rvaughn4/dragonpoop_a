
/*
*/

#include "dpgui_taskman.h"
#include "../../../dpcore/dptaskmgr/dptaskmgr_readlock.h"

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
        dptaskmgr_readlock *l;
        dpshared_guard g;
        uint64_t t;
        std::string s;

        if( !this->dpgui_window::onGuiRun( tl ) )
            return 0;

        t = this->getTicks();
        if( t - this->t < 2000 )
            return 1;
        this->t = t;

        l = this->getTaskMgr( &g, 100 );
        if( !l )
            return 1;

        l->getSummary( &s );
        this->setText( s.c_str() );
        this->redrawFg();

        return 1;
    }

}








