
/*
*/

#ifndef dprender_gui_writelock_h
#define dprender_gui_writelock_h

#include "../dprender_gui_list/dprender_gui_list_writelock.h"

namespace dp
{

    class dprender_gui;
    class dpapi_context_writelock;
    class dpapi_commandlist_writelock;
    class dpmatrix;
    struct dpinput_event;
    struct dpbitmap_rectangle;

    class dprender_gui_writelock : public dprender_gui_list_writelock
    {

        dprender_gui *p;

    private:

    protected:

        //dtor
        virtual ~dprender_gui_writelock( void );

    public:

        //ctor
        dprender_gui_writelock( dprender_gui *p, dpmutex_writelock *ml );
        //return z
        unsigned int getZ( void );
        //pass in context
        void passContext( dpapi_context_writelock *ctx );
        //render
        void render( dpmatrix *m_world, dpbitmap_rectangle *rc_world, dpmatrix *m_parent, dpbitmap_rectangle *rc_parent, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll );
        //process input event
        bool processEvent( dpinput_event *e );

    };

}

#endif







