

#include "dp/dpcore/dptaskmgr/dptaskmgr.h"

#include <iostream>
#include <thread>

int main()
{

    dp::dptaskmgr *tmgr;

    tmgr = new dp::dptaskmgr( 4 );


    std::this_thread::sleep_for( std::chrono::milliseconds( 5000 ) );


    delete tmgr;


    return 0;
}
