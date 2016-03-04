

#include "dp/dpcore/dptaskmgr/dptaskmgr.h"
#include "dp/dpcore/dptaskmgr/dptaskmgr_writelock.h"
#include "dp/dprender/dpapi/dpapi/dpapi/dpapi_factory.h"
#include "dp/dprender/dpapi/dpapi_task/dpapi_task.h"

#include <iostream>
#include <thread>

int main()
{

    dp::dptaskmgr *tmgr;
    dp::dpshared_guard g;
    dp::dpapi_task *wt;
    dp::dptaskmgr_writelock *tmgrl;

    tmgr = new dp::dptaskmgr( 4 );

    wt = new dp::dpapi_task( new dp::dpapi_factory( ) );

    tmgrl = (dp::dptaskmgr_writelock *)dpshared_guard_writeLock_block( g, tmgr );
    tmgrl->addStaticTask( wt, 1 );
    g.release( tmgrl );

    std::this_thread::sleep_for( std::chrono::milliseconds( 15000 ) );


    delete tmgr;
    delete wt;


    return 0;
}
