
/*
*/

#ifndef dpgui_window_zoom_out_button_h
#define dpgui_window_zoom_out_button_h

#include "../dpgui_button/dpgui_button.h"

namespace dp
{

    class dpgui_ref;

    class dpgui_window_zoom_out_button : public dpgui_button
    {

    private:

        dpgui_ref *pgui;
        dpshared_guard g;

    protected:

        //override to handle left clicks
        virtual void onLeftClick( dpinput_event_mouse *e );

    public:

        //ctor
        dpgui_window_zoom_out_button( int x, int y, unsigned int w, unsigned int h, dpgui_ref *pgui );
        //dtor
        virtual ~dpgui_window_zoom_out_button( void );

    };

}

#endif






