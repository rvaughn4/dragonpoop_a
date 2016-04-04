
/*
*/

#ifndef dpgui_list_ref_h
#define dpgui_list_ref_h

#include "../../dpcore/dptask/dptask_ref.h"

namespace dp
{

    class dpgui_list;

    class dpgui_list_ref : public dptask_ref
    {

    private:

        dpgui_list *p;

    protected:

        //dtor
        virtual ~dpgui_list_ref( void );

    public:

        //ctor
        dpgui_list_ref( dpgui_list *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpgui_list;
    };

}

#endif






