
/*

dpspinlock class
generic spinlock used to implement mutex
*/

#include "dpspinlock.h"
#include <thread>

namespace dp
{

    //ctor
    dpspinlock::dpspinlock( void )
    {
        this->unlock();
    }

    //dtor
    dpspinlock::~dpspinlock( void )
    {
    }

    //locks blocking
    void dpspinlock::lock( void )
    {
        volatile bool b;

        b = 1;
        while( b )
        {
            __asm volatile ("pause" ::: "memory");
            b = this->f.test_and_set( std::memory_order_acquire );
        }
    }

    //unlocks
    void dpspinlock::unlock( void )
    {
        this->f.clear( std::memory_order_release );
    }

};

