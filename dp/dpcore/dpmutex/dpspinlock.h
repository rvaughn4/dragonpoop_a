
/*

dpspinlock class header
generic spinlock used to implement mutex
*/

#ifndef dpspinlock_h
#define dpspinlock_h

#include <atomic>

namespace dp
{

    class dpspinlock
    {

    private:

        //lock boolean with forced atomic access
        std::atomic_flag f = ATOMIC_FLAG_INIT;

    protected:

    public:

        //ctor
        dpspinlock( void );
        //dtor
        virtual ~dpspinlock( void );
        //lock blocking
        void lock( void );
        //lock with timeout
        bool lock( unsigned int ms );
        //unlocks
        void unlock( void );
        //returns current epoch time in seconds
        uint64_t getEpoch( void );
        //returns tickcount in ms
        uint64_t getTicks( void );

    };

};

#endif
