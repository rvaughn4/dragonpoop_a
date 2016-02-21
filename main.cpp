

#include "dp/dpcore/dpthread/dpthread.h"

#include "dp/dpcore/dpshared/dpshared_guard.h"
#include "dp/dpcore/dpshared/dpshared.h"
#include "dp/dpcore/dpshared/dpshared_ref.h"
#include "dp/dpcore/dpshared/dpshared_readlock.h"
#include "dp/dpcore/dpshared/dpshared_writelock.h"

#include <iostream>
#include <thread>

int main()
{

    dp::dpshared_guard g;
    dp::dpthread *tr;
    dp::dpshared *m;
    dp::dpshared_ref *mr;
    dp::dpshared_readlock *mr1, *mr2;
    dp::dpshared_writelock *mw1, *mw2;

    tr = new dp::dpthread();

    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

    m = new dp::dpshared();

    mw1 = dpshared_guard_tryWriteLock_timeout( g, m, 1000 );
    mw2 = dpshared_guard_tryWriteLock_timeout( g, m, 1000 );
    mr1 = dpshared_guard_tryReadLock_timeout( g, m, 1000 );
    mr2 = dpshared_guard_tryReadLock_timeout( g, m, 1000 );

    mr = g.getRef( m );
    g.release( mw1 );

    std::this_thread::sleep_for( std::chrono::milliseconds( 2000 ) );


    mr1 = dpshared_guard_tryReadLock_timeout( g, mr, 1000 );
    mr2 = dpshared_guard_tryReadLock_timeout( g, mr, 1000 );
    mw1 = dpshared_guard_tryWriteLock_timeout( g, mr, 1000 );
    mw2 = dpshared_guard_tryWriteLock_timeout( g, mr, 1000 );
    g.release( mr1 );
    g.release( mr2 );

std::cout << "\r\n\r\n\r\n";

std::cout.flush();

    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

    delete tr;

    delete m;
    g.release( mr );



    return 0;
}
