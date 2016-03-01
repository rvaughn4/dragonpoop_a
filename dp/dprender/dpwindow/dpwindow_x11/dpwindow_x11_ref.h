
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpwindow_x11_ref_h
#define dpwindow_x11_ref_h

#include "../dpwindow/dpwindow_ref.h"

namespace dp
{

    class dpwindow_x11;

    class dpwindow_x11_ref : public dpwindow_ref
    {

    private:

        dpwindow_x11 *p;

    protected:

        //dtor
        virtual ~dpwindow_x11_ref( void );

    public:

        //ctor
        dpwindow_x11_ref( dpwindow_x11 *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpwindow_x11;
    };

}

#endif






