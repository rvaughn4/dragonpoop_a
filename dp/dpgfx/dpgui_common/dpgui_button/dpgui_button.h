
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

        bool bWasClicked, bDown;

    protected:

        //override to handle left clicks
        virtual void onLeftClick( dpinput_event_mouse *e );
        //override to handle mouse movement
        virtual void onMouseMove( dpinput_event_mouse *e );

    public:

        //ctor
        dpgui_button( int x, int y, unsigned int w, unsigned int h, const char *ctxt );
        //dtor
        virtual ~dpgui_button( void );
        //returns true if clicked
        bool wasClicked( void );

    };

}

#endif





