

#include "dp/dpcore/dptaskmgr/dptaskmgr.h"
#include "dp/dpcore/dptaskmgr/dptaskmgr_writelock.h"
#include "dp/dprender/dpapi/dpapi_x11_opengl1o5/dpapi_x11_opengl1o5/dpapi_x11_opengl1o5_factory.h"
#include "dp/dprender/dprender/dprender/dprender.h"
#include "dp/dprender/dprender/dprender/dprender_writelock.h"
#include "dp/dprender/dprender/dprender_scene/dprender_scene.h"

#include "dp/dpgfx/dpgfx/dpgfx.h"
#include "dp/dpgfx/dpgfx/dpgfx_writelock.h"
#include "dp/dpgfx/dpscene/dpscene.h"

#include <thread>

int main()
{
    dp::dptaskmgr *tmgr;
    dp::dpshared_guard g;
    dp::dptaskmgr_writelock *tmgrl;
    dp::dpgfx *gf;
    dp::dpgfx_writelock *gfl;
    dp::dpscene *scn;

    tmgr = new dp::dptaskmgr( 4 );

    gf = new dp::dpgfx();

    tmgrl = (dp::dptaskmgr_writelock *)dpshared_guard_writeLock_block( g, tmgr );
    tmgrl->addStaticTask( gf, 1 );
    g.release( tmgrl );

    scn = new dp::dpscene();

    gfl = (dp::dpgfx_writelock *)dpshared_guard_writeLock_block( g, gf );
    gfl->addScene( &scn );
    g.release( gfl );

    std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );


    std::this_thread::sleep_for( std::chrono::milliseconds( 4000 ) );

    delete gf;
    delete tmgr;

    return 0;
}
