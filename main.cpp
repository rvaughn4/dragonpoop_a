

#include "dp/dpmutex/dpmutex.h"
#include "dp/dpmutex/dpmutex_readlock.h"
#include "dp/dpmutex/dpmutex_writelock.h"


int main()
{

    dp::dpmutex *m;
    dp::dpmutex_readlock *mr1, *mr2;
    dp::dpmutex_writelock *mw1, *mw2;

    m = new dp::dpmutex();

    mw1 = dpmutex_tryWriteLock_timeout( m, 1000 );
    mw2 = dpmutex_tryWriteLock_timeout( m, 1000 );
    mr1 = dpmutex_tryReadLock_timeout( m, 1000 );
    mr2 = dpmutex_tryReadLock_timeout( m, 1000 );

    delete mw1;

    mr1 = dpmutex_tryReadLock_timeout( m, 1000 );
    mr2 = dpmutex_tryReadLock_timeout( m, 1000 );
    mw1 = dpmutex_tryWriteLock_timeout( m, 1000 );
    mw2 = dpmutex_tryWriteLock_timeout( m, 1000 );
    delete mr1;
    delete mr2;

    delete m;


    return 0;
}
