
/*
*/

#ifndef dprender_gui_ref_h
#define dprender_gui_ref_h

#include "../dprender_gui_list/dprender_gui_list_ref.h"

namespace dp
{

    class dprender_gui;

    class dprender_gui_ref : public dprender_gui_list_ref
    {

    private:

        dprender_gui *p;

    protected:

        //dtor
        virtual ~dprender_gui_ref( void );

    public:

        //ctor
        dprender_gui_ref( dprender_gui *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dprender_gui;
    };

}

#endif






