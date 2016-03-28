
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

    dp::dpbitmap *b_in, *b_out;
    dp::dpbitmap_loader bpl;
    //dpbitmap_32bit_uncompressed
    //dpbitmap_png
    //dpbitmap_png_bitmap

    b_in = bpl.load( "32bitsample.bmp" );
    b_out = new dp::dpbitmap_png( b_in->getWidth(), b_in->getHeight() );

    b_out->copy( b_in );
    b_out->save( "z_out.png" );

    return 0;
}
