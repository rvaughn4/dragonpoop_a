
/*
handles safe deletion of shared object refs
*/

#ifndef dpshared_ref_kernel_h
#define dpshared_ref_kernel_h

#include "dpshareddefines.h"
#include <atomic>

namespace dp
{

    class dpshared_ref_kernel
    {

    private:

        std::atomic<bool> bLinked;

    protected:

    public:

        //ctor
        dpshared_ref_kernel( void );
        //dtor
        virtual ~dpshared_ref_kernel( void );
        //returns true if linked
        bool isLinked( void );
        //unlink
        void unlink( void );

    };

}

#endif


