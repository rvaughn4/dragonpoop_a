
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
#include <fstream>

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

    dp::dpbuffer_dynamic bib;
    int v;

    std::fstream ff;

    ff.open( "8bitsample.bmp", ff.binary | ff.in );

    while( (v = ff.get() ) != EOF )
        bib.writeAlignedByte( v );
    ff.close();

    dp::dpbitmap *bi = new dp::dpbitmap_8bit_palette( &bib );
    dp::dpbitmap *b = new dp::dpbitmap_32bit_uncompressed( bi->getWidth(), bi->getHeight() );

    b->copy( bi );

    std::fstream f;

    f.open( "test1234.bmp", f.binary | f.out | f.trunc );
    f.write( b->getBuffer(), b->getSize() );
    f.close();

    delete bi;
    delete b;
    return 0;
}
