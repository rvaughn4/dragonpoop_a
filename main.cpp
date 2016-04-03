

#include "dp/dpcore/dptaskmgr/dptaskmgr.h"
#include "dp/dpcore/dptaskmgr/dptaskmgr_writelock.h"
#include "dp/dprender/dpapi/dpapi_x11_opengl1o5/dpapi_x11_opengl1o5/dpapi_x11_opengl1o5_factory.h"
#include "dp/dprender/dprender/dprender/dprender.h"
#include "dp/dprender/dprender/dprender/dprender_writelock.h"
#include "dp/dprender/dprender/dprender_scene/dprender_scene.h"

#include <thread>

#include "dp/dpgfx/dpbitmap/dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_16bit_uncompressed/dpbitmap_16bit_uncompressed.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_png/dpbitmap_png.h"
#include "dp/dpgfx/dpbitmap/dpbitmap_loader/dpbitmap_loader.h"
#include "dp/dpgfx/dpfont/dpfont/dpfont.h"

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

    std::this_thread::sleep_for( std::chrono::milliseconds( 4000 ) );

    delete sc;
    delete wt;
    delete tmgr;
*/

    dp::dpfont f;
    dp::dpbitmap_loader bml;
    dp::dpbitmap *bmf = bml.load( "picture.png" );
    dp::dpbitmap *bm = new dp::dpbitmap_png( 300, 300 );

    bm->copy( bmf );
    delete bmf;

    f.setSize( 40 );
    f.openFont( "sans" );
    std::string ss( "Hello, [color ff00ffff]how [size 50]are you? 1234567890 abcdefghijklmno pqrstuvwxyz" );

    f.drawString( &ss, 0, 0, bm );

    bm->save( "derp.png" );
    delete bm;

    return 0;
}
