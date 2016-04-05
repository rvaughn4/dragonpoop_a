
/*
*/

#ifndef dprender_gui_list_ref_h
#define dprender_gui_list_ref_h

#include "../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dprender_gui_list;

    class dprender_gui_list_ref : public dpshared_ref
    {

    private:

        dprender_gui_list *p;

    protected:

        //dtor
        virtual ~dprender_gui_list_ref( void );

    public:

        //ctor
        dprender_gui_list_ref( dprender_gui_list *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dprender_gui_list;
    };

}

#endif







