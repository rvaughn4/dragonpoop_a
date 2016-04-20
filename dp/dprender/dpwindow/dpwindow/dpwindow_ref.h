
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpwindow_ref_h
#define dpwindow_ref_h

#include "../../dpinput/dpinput_ref.h"

namespace dp
{

    class dpwindow;

    class dpwindow_ref : public dpinput_ref
    {

    private:

        dpwindow *p;

    protected:

        //dtor
        virtual ~dpwindow_ref( void );

    public:

        //ctor
        dpwindow_ref( dpwindow *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpwindow;
    };

}

#endif





