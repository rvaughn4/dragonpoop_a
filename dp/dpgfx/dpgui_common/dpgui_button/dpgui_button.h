
/*
*/

#ifndef dpgui_button_h
#define dpgui_button_h

#include "../../dpgui/dpgui.h"

namespace dp
{

    class dpgui_button : public dpgui
    {

    private:

        bool bWasClicked;

    protected:

        //override to handle left clicks
        virtual void onLeftClick( dpinput_event_mouse *e );

    public:

        //ctor
        dpgui_button( int x, int y, unsigned w, unsigned h, const char *ctxt );
        //dtor
        virtual ~dpgui_button( void );
        //returns true if clicked
        bool wasClicked( void );

    };

}

#endif





