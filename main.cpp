

#include "dp/dpcore/dptaskmgr/dptaskmgr.h"
#include "dp/dpcore/dptaskmgr/dptaskmgr_writelock.h"
#include "dp/dprender/dpwindow/dpwindow/dpwindow_factory.h"
#include "dp/dprender/dpwindow/dpwindow_task/dpwindow_task.h"

#include <iostream>
#include <thread>

int main()
{

    dp::dptaskmgr *tmgr;
    dp::dpshared_guard g;
    dp::dpwindow_task *wt;
    dp::dptaskmgr_writelock *tmgrl;

    tmgr = new dp::dptaskmgr( 4 );

    wt = new dp::dpwindow_task( new dp::dpwindow_factory() );

    tmgrl = (dp::dptaskmgr_writelock *)dpshared_guard_writeLock_block( g, tmgr );
    tmgrl->addStaticTask( wt, 1 );
    g.release( tmgrl );

    std::this_thread::sleep_for( std::chrono::milliseconds( 5000 ) );


    delete tmgr;
    delete wt;


    return 0;
}
