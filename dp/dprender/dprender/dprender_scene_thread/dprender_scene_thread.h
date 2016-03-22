
/*

*/

#ifndef dprender_scene_thread_h
#define dprender_scene_thread_h

#include "../../../dpcore/dptask/dptask.h"
#include <atomic>

namespace dp
{

    class dprender_scene_thread_writelock;
    class dpapi_commandlist;
    class dpapi_context;
    class dpapi_context_writelock;
    class dpapi_commandlist_writelock;

    class dprender_scene_thread : public dptask
    {

    private:

        dpapi_context *ctx;
        dpapi_commandlist *cl_a, *cl_b, *cl_next, *cl_prev;
        std::atomic<bool> *flag_a, *flag_b, *flag_next, *flag_prev;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to do task execution
        virtual bool onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual bool onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual bool onTaskStop( dptask_writelock *tl );
        //override to handle scene start
        virtual bool onSceneStart( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx );
        //override to handle scene stop/cleanup
        virtual bool onSceneStop( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx );
        //override to handle scene render
        virtual bool onSceneRender( dprender_scene_thread_writelock *l, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll );

    public:

        //ctor
        dprender_scene_thread( dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b );
        //dtor
        virtual ~dprender_scene_thread( void );

        friend class dprender_scene_thread_writelock;
        friend class dprender_scene_thread_readlock;
    };

}

#endif







