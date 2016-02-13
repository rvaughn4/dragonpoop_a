

#include "dp/dpcore/dpshared/dpshared.h"
#include "dp/dpcore/dpshared/dpshared_readlock.h"
#include "dp/dpcore/dpshared/dpshared_writelock.h"

#include <iostream>
int main()
{

    dp::dpshared *m;
    dp::dpshared_readlock *mr1, *mr2;
    dp::dpshared_writelock *mw1, *mw2;

    m = new dp::dpshared();

    mw1 = dpshared_tryWriteLock_timeout( m, 1000 );
    mw2 = dpshared_tryWriteLock_timeout( m, 1000 );
    mr1 = dpshared_tryReadLock_timeout( m, 1000 );
    mr2 = dpshared_tryReadLock_timeout( m, 1000 );

    delete mw1;

    mr1 = dpshared_tryReadLock_timeout( m, 1000 );
    mr2 = dpshared_tryReadLock_timeout( m, 1000 );
    mw1 = dpshared_tryWriteLock_timeout( m, 1000 );
    mw2 = dpshared_tryWriteLock_timeout( m, 1000 );
    delete mr1;
    delete mr2;

std::cout << "\r\n\r\n\r\n";

    delete m;



    return 0;
}
