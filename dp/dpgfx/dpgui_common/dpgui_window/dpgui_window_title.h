
/*
*/

#ifndef dpgui_window_title_h
#define dpgui_window_title_h

#include "../../dpgui/dpgui.h"
#include "../../dpgui/dpgui_ref.h"

namespace dp
{

    class dpgui_window_title : public dpgui
    {

    private:

        dpgui_ref *pgui;
        dpshared_guard g;

    protected:

        //render first pass background image
        virtual void renderBackgroundPass0( dpbitmap *bm );
        //render first pass background image
        virtual void renderBackgroundPass1( dpbitmap *bm );
        //override to handle gui start
        virtual bool onGuiStart( dpgui_writelock *tl );

    public:

        //ctor
        dpgui_window_title( int x, int y, unsigned int w, unsigned int h, const char *ctxt, dpgui *pgui );
        //dtor
        virtual ~dpgui_window_title( void );

    };

}

#endif







