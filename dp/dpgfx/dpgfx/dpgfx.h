
/*
gpgfx manages models and gui elements and scenes
*/

#ifndef dpgfx_h
#define dpgfx_h

#include "../../dpcore/dptask/dptask.h"

namespace dp
{

    class dpgfx : public dptask
    {

    private:

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to do task execution
        virtual void onTaskRun( dpthread_writelock *thd, dptask_writelock *tl );
        //override to do task startup
        virtual void onTaskStart( dpthread_writelock *thd, dptask_writelock *tl );
        //override to do task shutdown
        virtual void onTaskStop( dpthread_writelock *thd, dptask_writelock *tl );

    public:

        //ctor
        dpgfx( void );
        //dtor
        virtual ~dpgfx( void );

        friend class dpgfx_writelock;
        friend class dpgfx_readlock;
    };

}

#endif





