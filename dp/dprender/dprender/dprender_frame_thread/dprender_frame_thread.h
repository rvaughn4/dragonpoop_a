
/*

*/

#ifndef dprender_frame_thread_h
#define dprender_frame_thread_h

#include "../../../dpcore/dptask/dptask.h"
#include <atomic>

namespace dp
{

    class dprender_frame_thread_writelock;
    class dpapi_primary_commandlist;
    class dpapi_context;
    class dprender_writelock;
    class dprender_scene;
    class dprender_scene_ref;
    class dpapi_writelock;
    class dpapi_context_writelock;
    class dpapi_primary_commandlist_writelock;

    #define dprender_frame_thread_MAX_scenes 64

    class dprender_frame_thread : public dptask
    {

    private:

        dpapi_context *ctx;
        dpapi_primary_commandlist *cl_a, *cl_b, *cl_next, *cl_prev;
        std::atomic<bool> *flag_a, *flag_b, *flag_next, *flag_prev;
        dprender_scene_ref *scenes[ dprender_frame_thread_MAX_scenes ];
        dpshared_guard g;

        //zero scenes
        void zeroScenes( void );
        //delete scenes
        void deleteScenes( void );
        //draw scenes
        void drawScenes( dpapi_context_writelock *ctxl, dpapi_primary_commandlist_writelock *cll );
        //add scene
        bool _addScene( dprender_scene *s );
        //stop all scenes or return zero if not stopped
        bool stopScenes( void );

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
        //add scene
        bool addScene( dprender_scene *s, dpapi_writelock *apil, dprender_writelock *rl, dprender_frame_thread_writelock *tl );
        //remove scene
        void removeScene( dprender_scene *s, dprender_writelock *rl, dprender_frame_thread_writelock *tl );

    public:

        //ctor
        dprender_frame_thread( dpapi_context *ctx, dpapi_primary_commandlist *cl_a, dpapi_primary_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b );
        //dtor
        virtual ~dprender_frame_thread( void );

        friend class dprender_frame_thread_writelock;
        friend class dprender_frame_thread_readlock;
    };

}

#endif






