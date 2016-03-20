
/*

*/

#ifndef dprender_gui_thread_h
#define dprender_gui_thread_h

#include "../../../dpcore/dptask/dptask.h"
#include <atomic>

namespace dp
{

    class dprender_gui_thread_writelock;
    class dpapi_commandlist;
    class dpapi_context;
    class dpapi_vertexbuffer;
    class dpapi_indexbuffer;
    class dpapi_bundle;

    class dprender_gui_thread : public dptask
    {

    private:

        dpapi_context *ctx;
        dpapi_commandlist *cl_a, *cl_b, *cl_next, *cl_prev;
        std::atomic<bool> *flag_a, *flag_b, *flag_next, *flag_prev;

        dpapi_vertexbuffer *vb;
        dpapi_indexbuffer *ib;
        dpapi_bundle *bdle;

    protected:

        //override to do task execution
        virtual bool onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual bool onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual bool onTaskStop( dptask_writelock *tl );

    public:

        //ctor
        dprender_gui_thread( dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b );
        //dtor
        virtual ~dprender_gui_thread( void );

        friend class dprender_gui_thread_writelock;
        friend class dprender_gui_thread_readlock;
    };

}

#endif







