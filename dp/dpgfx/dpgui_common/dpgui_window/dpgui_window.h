
/*
*/

#ifndef dpgui_window_h
#define dpgui_window_h

#include "../../dpgui/dpgui.h"

namespace dp
{

    class dpgui_window : public dpgui
    {

    private:

        std::string stitle;

    protected:

        //render first pass background image
        virtual void renderBackgroundPass0( dpbitmap *bm );
        //render first pass background image
        virtual void renderBackgroundPass1( dpbitmap *bm );
        //override to handle gui start
        virtual bool onGuiStart( dpgui_writelock *tl );

    public:

        //ctor
        dpgui_window( int x, int y, unsigned int w, unsigned int h, const char *ctitle, const char *ctxt );
        //dtor
        virtual ~dpgui_window( void );

    };

}

#endif






