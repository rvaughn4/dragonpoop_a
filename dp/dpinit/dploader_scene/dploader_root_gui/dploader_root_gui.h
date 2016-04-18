
/*
*/

#ifndef dploader_root_gui_h
#define dploader_root_gui_h

#include "../../../dpgfx/dpgui/dpgui.h"

namespace dp
{

    class dploader_root_gui : public dpgui
    {

    private:

    protected:

        //render first pass background image
        virtual void renderBackgroundPass0( dpbitmap *bm );
        //override to handle gui ran
        virtual bool onGuiRun( dpgui_writelock *tl );
        //override to handle gui start
        virtual bool onGuiStart( dpgui_writelock *tl );
        //override to handle gui stop
        virtual bool onGuiStop( dpgui_writelock *tl );

    public:

        //ctor
        dploader_root_gui( void );
        //dtor
        virtual ~dploader_root_gui( void );

    };

}

#endif





