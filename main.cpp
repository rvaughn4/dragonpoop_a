

#include "dp/dpcore/dpthread/dpthread.h"


#include "dp/dpcore/dpshared/dpshared.h"
#include "dp/dpcore/dpshared/dpshared_ref.h"
#include "dp/dpcore/dpshared/dpshared_readlock.h"
#include "dp/dpcore/dpshared/dpshared_writelock.h"

#include <iostream>
#include <thread>

int main()
{

    dp::dpthread *tr;
    dp::dpshared *m;
    dp::dpshared_ref *mr;
    dp::dpshared_readlock *mr1, *mr2;
    dp::dpshared_writelock *mw1, *mw2;

    tr = new dp::dpthread();

    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

    m = new dp::dpshared();

    mw1 = dpshared_tryWriteLock_timeout( m, 1000 );
    mw2 = dpshared_tryWriteLock_timeout( m, 1000 );
    mr1 = dpshared_tryReadLock_timeout( m, 1000 );
    mr2 = dpshared_tryReadLock_timeout( m, 1000 );

    mr = mw1->getRef();
    delete mw1;

    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );


    mr1 = dpshared_tryReadLock_timeout( mr, 1000 );
    mr2 = dpshared_tryReadLock_timeout( mr, 1000 );
    mw1 = dpshared_tryWriteLock_timeout( mr, 1000 );
    mw2 = dpshared_tryWriteLock_timeout( mr, 1000 );
    delete mr1;
    delete mr2;

std::cout << "\r\n\r\n\r\n";

std::cout.flush();

    std::this_thread::sleep_for( std::chrono::milliseconds( 200 ) );

    delete tr;

    delete m;
    delete mr;



    return 0;
}
