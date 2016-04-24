
/*
*/

#include "dpgui_button.h"

namespace dp
{

    //ctor
    dpgui_button::dpgui_button( int x, int y, unsigned w, unsigned h, const char *ctxt ) : dpgui( x, y, w, h, ctxt )
    {
        this->bWasClicked = 0;
    }

    //dtor
    dpgui_button::~dpgui_button( void )
    {

    }

    //returns true if clicked
    bool dpgui_button::wasClicked( void )
    {
        bool r;

        r = this->bWasClicked;
        this->bWasClicked = 0;

        return r;
    }

    //override to handle left clicks
    void dpgui_button::onLeftClick( dpinput_event_mouse *e )
    {
        this->bWasClicked = 1;
    }

}







