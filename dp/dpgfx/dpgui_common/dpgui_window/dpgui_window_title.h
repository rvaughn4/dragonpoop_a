
/*
*/

#ifndef dpgui_window_title_h
#define dpgui_window_title_h

#include "../../dpgui/dpgui.h"

namespace dp
{

    class dpgui_window_title : public dpgui
    {

    private:

    protected:

        //render first pass background image
        virtual void renderBackgroundPass0( dpbitmap *bm );
        //render first pass background image
        virtual void renderBackgroundPass1( dpbitmap *bm );

    public:

        //ctor
        dpgui_window_title( int x, int y, unsigned int w, unsigned int h, const char *ctxt );
        //dtor
        virtual ~dpgui_window_title( void );

    };

}

#endif







