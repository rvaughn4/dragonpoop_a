

#include "dp/dpcore/dpthread/dpthread.h"
#include "dp/dpcore/dpthread/dpthread_writelock.h"
#include "dp/dpcore/dptask/dptask.h"

#include "dp/dpcore/dpshared/dpshared_guard.h"

#include <iostream>
#include <thread>

int main()
{

    dp::dpshared_guard g;
    dp::dpthread *tr;
    dp::dpthread_writelock *trl;
    dp::dptask *tsk;

    tr = new dp::dpthread();
    tsk = new dp::dptask();

    trl = (dp::dpthread_writelock *)dpshared_guard_writeLock_block( g, tr );
    trl->addStaticTask( tsk, 1 );
    g.release( trl );

    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

    std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );

std::cout.flush();

    delete tsk;
    delete tr;

    return 0;
}
