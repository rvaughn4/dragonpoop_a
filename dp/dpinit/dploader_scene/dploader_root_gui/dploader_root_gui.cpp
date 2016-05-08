
/*
*/

#include "dploader_root_gui.h"
#include "../../../dpgfx/dpbitmap/dpbitmap_loader/dpbitmap_loader.h"

namespace dp
{

    //ctor
    dploader_root_gui::dploader_root_gui( void ) : dpgui_window( 0, 0, 1000, 300, "Dragon Poop V0.1 ALPHA", "", 50 )
    {
        this->setFontSize( 40 );
        this->setCentered( 1 );
        this->setText( "\n[size 120][face mediaeval]\t\tDragon Poop\n[align center][size 30][face sans]\n\tA very serious gaming SDK. It's as smooth as silk and runs like warm milk.[size 15]\n[code 178]2016 RAV. If you steal this we will beat you up!" );

        this->setInputMode( 1 );
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

        rc.w = 260;
        rc.h = 200;
        rc.x = 30;
        rc.y = ( bm->getHeight() - rc.h ) / 2;

        bm->copyInto( b, &rc );
    }

}






