
/*
*/

#include "dploader_root_gui.h"
#include "../../../dpgfx/dpbitmap/dpbitmap_loader/dpbitmap_loader.h"
#include "../../../dpgfx/dpgui_common/dpgui_taskman/dpgui_taskman.h"

namespace dp
{

    //ctor
    dploader_root_gui::dploader_root_gui( void ) : dpgui_window( 0, 0, 1000, 300, "Dragon Poop V0.1 ALPHA", "", 50 )
    {
        dpgui_attribs a;

        this->getAttributes( &a );

        a.bIsCenter = 1;
        a.bIsInput = 1;
        a.fnt_size = 40;

        this->setAttributes( &a );

        this->setText( "\n[size 120][face mediaeval]\t\tDragon Poop\n[align center][size 30][face sans]\n\tA very serious gaming SDK. It's as smooth as silk and runs like warm milk.[size 15]\n[code 178]2016 RAV. If you steal this we will beat you up!" );
    }

    //dtor
    dploader_root_gui::~dploader_root_gui( void )
    {

    }

    //render first pass of foreground image
    void dploader_root_gui::renderBackgroundPass1( dpbitmap_32bit_uncompressed *bm )
    {
        dpbitmap_loader bl;
        dpbitmap *b;
        dpbitmap_rectangle rc;

        this->dpgui_window::renderBackgroundPass1( bm );

        bm->setTransparencyMode( dpbitmap_transparency_mode_blend );
        b = bl.load( "dp.png" );
        if( !b )
            return;

        rc.w = 20;
        rc.h = 70;
        rc.x = 5;
        rc.y = 5;
        bm->convertFromPercents( &rc );

        bm->copyInto( b, &rc );
    }

    //override to handle gui start
    bool dploader_root_gui::onGuiStart( dpgui_writelock *tl )
    {
        dpgui *g;

        if( !this->dpgui_window::onGuiStart( tl ) )
            return 0;

        g = new dpgui_taskman();
        this->addGui( &g, 1 );

        return 1;
    }

}






