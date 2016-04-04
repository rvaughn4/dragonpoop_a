
/*
*/

#ifndef dpgui_ref_h
#define dpgui_ref_h

#include "../dpgui_list/dpgui_list_ref.h"

namespace dp
{

    class dpgui;

    class dpgui_ref : public dpgui_list_ref
    {

    private:

        dpgui *p;

    protected:

        //dtor
        virtual ~dpgui_ref( void );

    public:

        //ctor
        dpgui_ref( dpgui *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dpgui;
    };

}

#endif





