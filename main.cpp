

#include "dp/dpcore/dpthread/dpthread.h"

#include "dp/dpcore/dpshared/dpshared_guard.h"

#include <iostream>
#include <thread>

int main()
{

    dp::dpshared_guard g;
    dp::dpthread *tr;

    tr = new dp::dpthread();

    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

    std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );

std::cout.flush();

    delete tr;

    return 0;
}
