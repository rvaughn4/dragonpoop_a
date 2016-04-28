
/*
*/

#include "dploader_root_gui.h"
#include "../../../dpgfx/dpbitmap/dpbitmap_loader/dpbitmap_loader.h"

namespace dp
{

    //ctor
    dploader_root_gui::dploader_root_gui( void ) : dpgui( 0, 0, 1000, 300, "[align center][size 100]\r\nDragon Poop" )
    {

    }

    //dtor
    dploader_root_gui::~dploader_root_gui( void )
    {

    }

    //render first pass background image
    void dploader_root_gui::renderBackgroundPass0( dpbitmap *bm )
    {
        dpbitmap_loader ldr;
        dpbitmap *lbm = ldr.load( "picture.png" );

        if( !lbm )
            return;

        lbm->texturize( 1, 0.2f );
        bm->copy( lbm );
        bm->buttonize( 100, 1.0f, 0 );
        bm->sharpen( 0.7f );

        delete lbm;
    }

    //override to handle gui ran
    bool dploader_root_gui::onGuiRun( dpgui_writelock *tl )
    {
        return this->dpgui::onGuiRun( tl );
    }

    //override to handle gui start
    bool dploader_root_gui::onGuiStart( dpgui_writelock *tl )
    {
        return this->dpgui::onGuiStart( tl );
    }

    //override to handle gui stop
    bool dploader_root_gui::onGuiStop( dpgui_writelock *tl )
    {
        return this->dpgui::onGuiStop( tl );
    }

}






