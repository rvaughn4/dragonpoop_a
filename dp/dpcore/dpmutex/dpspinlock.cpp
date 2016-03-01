
/*

dpspinlock class
generic spinlock used to implement mutex
*/

#include "dpspinlock.h"
#include <thread>
#include <chrono>

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

    //locks blocking
    bool dpspinlock::lock( unsigned int wait_ms )
    {
        volatile bool b;
        uint64_t t_start, t_stop, t_now;

        t_start = t_now = this->getTicks();

        b = 1;
        t_stop = t_start + (uint64_t)wait_ms;
        while( b && t_now < t_stop )
        {
            __asm volatile( "pause" ::: "memory" );

            b = this->f.test_and_set( std::memory_order_acquire );
            t_now = this->getTicks();
        }

        return !b;
    }

    //unlocks
    void dpspinlock::unlock( void )
    {
        this->f.clear( std::memory_order_release );
    }

    //returns current epoch time in seconds
    uint64_t dpspinlock::getEpoch( void )
    {
        std::chrono::time_point<std::chrono::steady_clock> tp_now;
        std::chrono::steady_clock::duration d_s;

        tp_now = std::chrono::steady_clock::now();
        d_s = tp_now.time_since_epoch();

        return d_s.count() * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
    }

    //returns tickcount in ms
    uint64_t dpspinlock::getTicks( void )
    {
        std::chrono::time_point<std::chrono::steady_clock> tp_now;
        std::chrono::steady_clock::duration d_s;

        tp_now = std::chrono::steady_clock::now();
        d_s = tp_now.time_since_epoch();

        return d_s.count() * 1000 * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;
    }

};

