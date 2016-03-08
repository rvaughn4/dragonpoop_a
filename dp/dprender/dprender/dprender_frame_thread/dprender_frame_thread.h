
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

    class dprender_frame_thread : public dptask
    {

    private:

        dpapi_context *ctx;
        dpapi_primary_commandlist *cl_a, *cl_b, *cl_next, *cl_prev;
        std::atomic<bool> *flag_a, *flag_b, *flag_next, *flag_prev;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to do task execution
        virtual void onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual void onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual void onTaskStop( dptask_writelock *tl );

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






