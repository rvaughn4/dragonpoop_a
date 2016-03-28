
/*
#include "dp/dpcore/dptaskmgr/dptaskmgr.h"
#include "dp/dpcore/dptaskmgr/dptaskmgr_writelock.h"
#include "dp/dprender/dpapi/dpapi_x11_opengl1o5/dpapi_x11_opengl1o5/dpapi_x11_opengl1o5_factory.h"
#include "dp/dprender/dprender/dprender/dprender.h"
#include "dp/dprender/dprender/dprender/dprender_writelock.h"
#include "dp/dprender/dprender/dprender_scene/dprender_scene.h"

#include <iostream>
#include <thread>
*/

#include "dp/dpgfx/dpbitmap/dpbitmap_loader/dpbitmap_loader.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_png/dpbitmap_png.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_png_bitmap/dpbitmap_png_bitmap.h"

int main()
{
/*
    dp::dptaskmgr *tmgr;
    dp::dpshared_guard g;
    dp::dprender *wt;
    dp::dprender_writelock *wtl;
    dp::dptaskmgr_writelock *tmgrl;
    dp::dprender_scene *sc;

    tmgr = new dp::dptaskmgr( 4 );

    wt = new dp::dprender( new dp::dpapi_x11_opengl1o5_factory( 1000, 1000, "hello there!" ) );

    tmgrl = (dp::dptaskmgr_writelock *)dpshared_guard_writeLock_block( g, tmgr );
    tmgrl->addStaticTask( wt, 1 );
    g.release( tmgrl );

    std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );

    sc = new dp::dprender_scene();
    wtl = (dp::dprender_writelock *)dpshared_guard_writeLock_block( g, wt );
    wtl->addScene( sc );
    g.release( wtl );

    std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );

    delete sc;
    delete wt;
    delete tmgr;
*/


 //   std::cout.flush();

    dp::dpbitmap *b_in_bmp, *b_out_png, *b_in_png, *b_out_bmp;
    dp::dpbitmap_loader bpl;

    b_in_bmp = bpl.load( "32bitsample.bmp" );
    b_out_png = new dp::dpbitmap_png( b_in_bmp->getWidth(), b_in_bmp->getHeight() );

    b_out_png->copy( b_in_bmp );
    b_out_png->save( "z_out.png" );

    delete b_in_bmp;
    delete b_out_png;

    b_in_png = bpl.load( "z_out.png" );
    b_out_bmp = new dp::dpbitmap_32bit_uncompressed( b_in_png->getWidth(), b_in_png->getHeight() );

    b_out_bmp->copy( b_in_png );
    b_out_bmp->save( "z_out.bmp" );

    delete b_in_png;
    delete b_out_bmp;

    return 0;
}
