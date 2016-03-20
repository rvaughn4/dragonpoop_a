
/*
handles safe deletion of shared object refs
*/

#ifndef dpshared_ref_kernel_h
#define dpshared_ref_kernel_h

#include "dpshareddefines.h"
#include <atomic>
#include "../dpmutex/dpspinlock.h"

namespace dp
{

    #define dpshared_ref_kernel_max 64
    class dpshared_ref;

    class dpshared_ref_kernel
    {

    private:

        std::atomic<bool> bLinked;
        dpspinlock s;

    protected:

    public:

        //ctor
        dpshared_ref_kernel( void );
        //dtor
        virtual ~dpshared_ref_kernel( void );
        //returns true if linked
        bool isLinked( void );
        //unlink all refs
        void unlink( void );
    };

}

#endif


