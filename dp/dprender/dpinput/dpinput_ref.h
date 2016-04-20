
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dpinput_ref_h
#define dpinput_ref_h

#include "../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dpinput;

    class dpinput_ref : public dpshared_ref
    {

    private:

        dpinput *p;

    protected:

        //dtor
        virtual ~dpinput_ref( void );

    public:

        //ctor
        dpinput_ref( dpinput *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpinput;
    };

}

#endif






