
/*

*/

#ifndef dprender_scene_h
#define dprender_scene_h

#include "../../../dpcore/dptask/dptask.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"
#include <atomic>

namespace dp
{

    class dprender_scene_writelock;
    class dprender_writelock;
    class dprender_gui_thread;
    class dpapi_context;
    class dpapi_commandlist;
    class dpapi_writelock;
    class dpapi_ref;
    class dprender_frame_thread_writelock;
    class dprender_writelock;
    class dprender_ref;

    struct dprender_scene_task
    {
        dptask *tsk;
        dpapi_context *ctx;
        struct
        {
            dpapi_commandlist *cl;
            std::atomic<bool> b;
        } a, b;
    };

    class dprender_scene : public dptask
    {

    private:

        dpapi_ref *apir;
        dpshared_guard g;
        dprender_ref *rr;

        struct
        {
            union
            {
                dprender_scene_task tsks[ 5 ];
                struct
                {
                    dprender_scene_task gui_task, model_task, sky_task, terrain_task, water_task;
                } tskname;
            };
        } tasks;

        //zero tasks
        void zeroTasks( void );
        //delete tasks and contexts
        void deleteTasksAndContexts( void );
        //make contexts
        bool makeContexts( dpapi_writelock *apil );
        //make tasks
        bool makeTasks( dprender_scene_writelock *l );

    protected:

        //attach scene to renderer
        bool attach( dpapi_writelock *apil, dprender_writelock *rl, dprender_frame_thread_writelock *tl );
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
        //generate gui task
        virtual dprender_gui_thread *makeGuiTask( dprender_scene_writelock *l, dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b );

    public:

        //ctor
        dprender_scene( void );
        //dtor
        virtual ~dprender_scene( void );

        friend class dprender_scene_writelock;
        friend class dprender_scene_readlock;
    };

}

#endif







