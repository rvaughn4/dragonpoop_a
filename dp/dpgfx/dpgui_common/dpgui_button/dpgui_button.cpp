
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
        dpgui_attribs a;

        this->bWasClicked = 0;
        this->bDown = 0;

        bw = 10.0f * 2.0f;
        if( bw > w )
            bw = w;
        if( bw > h )
            bw = h;
        bw = bw / 2.0f;

        this->getAttributes( &a );
        a.bGrows = 1;
        a.border_size = bw;
        this->setAttributes( &a );
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
        dpgui_attribs a;

        if( !this->bDown && !e->isRight && e->isDown )
        {
            this->getAttributes( &a );
            a.bBorderInvert = 1;
            this->setAttributes( &a );
            this->redrawBg();
            this->bDown = 1;
        }

        if( this->bDown && !e->isRight && !e->isDown )
        {
            this->getAttributes( &a );
            a.bBorderInvert = 0;
            this->setAttributes( &a );
            this->redrawBg();
            this->bDown = 0;
        }

        this->dpgui::onMouseMove( e );
    }

}







