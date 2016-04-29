
/*
*/

#include "dpgui_button.h"

namespace dp
{

    //ctor
    dpgui_button::dpgui_button( int x, int y, unsigned int w, unsigned int h, const char *ctxt ) : dpgui( x, y, w, h, ctxt )
    {
        this->bWasClicked = 0;
        this->setGrow( 1 );
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

    //render first pass background image
    void dpgui_button::renderBackgroundPass0( dpbitmap *bm )
    {
        dpbitmap_color c;
        c.r = c.g = c.b = c.a = 1;
        bm->fill( &c );
    }

    //render first pass background image
    void dpgui_button::renderBackgroundPass1( dpbitmap *bm )
    {
        bm->buttonize( 10, 0.5f, 0 );
    }

}







