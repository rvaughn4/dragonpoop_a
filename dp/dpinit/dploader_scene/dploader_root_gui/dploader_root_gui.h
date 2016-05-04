
/*
*/

#ifndef dploader_root_gui_h
#define dploader_root_gui_h

#include "../../../dpgfx/dpgui_common/dpgui_window/dpgui_window.h"

namespace dp
{

    class dploader_root_gui : public dpgui_window
    {

    private:

    protected:

        //render first pass of foreground image
        virtual void renderBackgroundPass1( dpbitmap_32bit_uncompressed *bm );

    public:

        //ctor
        dploader_root_gui( void );
        //dtor
        virtual ~dploader_root_gui( void );

    };

}

#endif





