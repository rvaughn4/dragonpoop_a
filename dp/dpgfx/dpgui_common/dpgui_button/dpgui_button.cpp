
/*
*/

#include "dpgui_button.h"
#include "../../../dprender/dpinput/dpinput.h"

namespace dp
{

    //ctor
    dpgui_button::dpgui_button( int x, int y, unsigned int w, unsigned int h, const char *ctxt ) : dpgui( x, y, w, h, ctxt )
    {
        float bw;

        this->bWasClicked = 0;
        this->setGrow( 1 );
        this->bDown = 0;

        bw = 10.0f * 2.0f;
        if( bw > w )
            bw = w;
        if( bw > h )
            bw = h;
        bw = bw / 2.0f;

        this->setBorderWidth( bw );
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
        this->dpgui::onLeftClick( e );
    }

    //override to handle mouse movement
    void dpgui_button::onMouseMove( dpinput_event_mouse *e )
    {

        if( !this->bDown && !e->isRight && e->isDown )
        {
            this->setBorderInverted( 1 );
            this->redrawBg();
            this->bDown = 1;
        }

        if( this->bDown && !e->isRight && !e->isDown )
        {
            this->setBorderInverted( 0 );
            this->redrawBg();
            this->bDown = 0;
        }

        this->dpgui::onMouseMove( e );
    }

}







