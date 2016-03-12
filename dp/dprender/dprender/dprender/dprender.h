
/*

*/

#ifndef dprender_h
#define dprender_h

#include "../../../dpcore/dptask/dptask.h"
#include "dprender_scenelink.h"
#include <atomic>

namespace dp
{

    class dprender_writelock;
    class dpapi_factory;
    class dpapi;
    class dpapi_context;
    class dpapi_primary_commandlist;
    class dprender_frame_thread;
    class dprender_scene;

    class dprender : public dptask
    {

    private:

        dpapi_factory *apifactory;
        dpapi *api;
        dpapi_context *main_ctx, *frame_ctx;
        dpapi_primary_commandlist *cl_a, *cl_b, *cl_next, *cl_prev;
        std::atomic<bool> flag_a, flag_b, *flag_next, *flag_prev;
        dprender_frame_thread *frametask;
        uint64_t t_last_f;
        unsigned int fps, f_last_t;
        dprender_scenelink_list scenes;
        dpshared_guard clg;

        //zero out scenes
        void zeroScenes( void );
        //delete scenes
        void deleteScenes( void );

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
        //make scene
        dprender_scene *makeScene( dprender_writelock *wl );

    public:

        //ctor
        dprender( dpapi_factory *wf );
        //dtor
        virtual ~dprender( void );
        //wait for flag to set or unset
        static bool waitForFlag( std::atomic<bool> *f, bool m, unsigned int wait_ms, dptask_writelock *l );

        friend class dprender_writelock;
        friend class dprender_readlock;
    };

}

#endif






