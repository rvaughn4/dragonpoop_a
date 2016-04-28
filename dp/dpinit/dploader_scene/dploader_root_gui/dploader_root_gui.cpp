
/*
*/

#include "dploader_root_gui.h"
#include "../../../dpgfx/dpbitmap/dpbitmap_loader/dpbitmap_loader.h"

namespace dp
{

    //ctor
    dploader_root_gui::dploader_root_gui( void ) : dpgui_window( 0, 0, 1000, 300, "Dragon Poop", "[align center][size 100]\r\nDragon Poop" )
    {
        //this->setCentered( 1 );
    }

    //dtor
    dploader_root_gui::~dploader_root_gui( void )
    {

    }

    //override to handle left clicks
    void dploader_root_gui::onKeyUp( dpinput_event_keypress *e )
    {
        this->dpgui_window::onKeyUp( e );
        this->setMinimized( !this->isMinimized() );
        this->update();
    }

}






