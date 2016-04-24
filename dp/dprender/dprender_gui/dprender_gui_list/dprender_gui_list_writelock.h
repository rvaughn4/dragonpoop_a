
/*
*/

#ifndef dprender_gui_list_writelock_h
#define dprender_gui_list_writelock_h

#include "../../../dpcore/dpshared/dpshared_writelock.h"

namespace dp
{

    class dprender_gui_list;
    class dprender_gui;
    class dpapi_context_writelock;
    class dpmatrix;
    class dpapi_commandlist_writelock;
    struct dpinput_event;
    struct dpbitmap_rectangle;

    class dprender_gui_list_writelock : public dpshared_writelock
    {

        dprender_gui_list *p;

    private:

    protected:

        //dtor
        virtual ~dprender_gui_list_writelock( void );

    public:

        //ctor
        dprender_gui_list_writelock( dprender_gui_list *p, dpmutex_writelock *ml );
        //add gui, starts task and takes ownership of gui, sets pointer to zero, use a ref to access
        bool addGui( dprender_gui **ngui );
        //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
        unsigned int getGuis( dprender_gui **glist, unsigned int max_cnt );
        //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
        unsigned int getGuisZSorted( dprender_gui **glist, unsigned int max_cnt, unsigned int *p_max_z, bool bInverted );
        //pass in context
        void passContext( dpapi_context_writelock *ctx );
        //render
        void render( dpmatrix *m_world, dpbitmap_rectangle *rc_world, dpmatrix *m_parent, dpbitmap_rectangle *rc_parent, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll );
        //process input event
        bool processEvent( dpinput_event *e );

    };

}

#endif








