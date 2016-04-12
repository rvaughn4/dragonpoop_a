
/*

*/

#ifndef dprender_h
#define dprender_h

#include "../../../dpcore/dptask/dptask.h"
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
    class dpgfx;
    class dpscene;

    #define dprender_max_scenes 64

    class dprender : public dptask
    {

    private:

        dpapi_factory *apifactory;
        dpapi *api;
        dpapi_context *main_ctx, *frame_ctx;
        dpapi_primary_commandlist *cl_a, *cl_b, *cl_next, *cl_prev;
        std::atomic<bool> flag_a, flag_b, *flag_next, *flag_prev;
        dprender_frame_thread *frametask;
        uint64_t t_last_f, t_last_clone;
        unsigned int fps, f_last_t;
        dpshared_guard clg;
        dpgfx *gfx;
        dprender_scene *scenes[ dprender_max_scenes ];

        //clone new scenes
        void cloneScenes( void );
        //look for scene
        dprender_scene *findScene( dpscene *s );
        //add new scene
        dprender_scene *addScene( dpscene *s );
        //remove old scenes
        void removeOldScenes( void );
        //stop scenes
        bool stopScenes( void );
        //delete scenes
        void deleteScenes( void );
        //zero scenes
        void zeroScenes( void );

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

    public:

        //ctor
        dprender( dpgfx *gfx, dpapi_factory *wf );
        //dtor
        virtual ~dprender( void );
        //wait for flag to set or unset
        static bool waitForFlag( std::atomic<bool> *f, bool m, unsigned int wait_ms, dptask_writelock *l );

        friend class dprender_writelock;
        friend class dprender_readlock;
    };

}

#endif






