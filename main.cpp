
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
#include "dp/dpgfx/dpbitmap/dpbitmap_1bit_palette/dpbitmap_1bit_palette.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_4bit_palette/dpbitmap_4bit_palette.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_8bit_palette/dpbitmap_8bit_palette.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_16bit_uncompressed/dpbitmap_16bit_uncompressed.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_24bit_uncompressed/dpbitmap_24bit_uncompressed.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_png/dpbitmap_png.h"

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

    dp::dpbitmap *bi = new dp::dpbitmap_8bit_palette( 32, 32 );

    bi->load( "8bitsample.bmp" );

    dp::dpbitmap *b = new dp::dpbitmap_32bit_uncompressed( bi->getWidth(), bi->getHeight() );
    dp::dpbitmap *bp = new dp::dpbitmap_png( 32, 32 );

    b->copy( bi );
    //bp->copy( b );

    b->save( "test1234.bmp" );
    bp->save( "test1234.png" );

    delete bi;
    delete b;
    delete bp;

    return 0;
}
