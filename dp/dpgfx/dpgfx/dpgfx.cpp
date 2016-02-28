
/*
gpgfx manages models and gui elements and scenes
*/

#include "dpgfx.h"
#include "dpgfx_ref.h"
#include "dpgfx_readlock.h"
#include "dpgfx_writelock.h"

namespace dp
{

   //ctor
    dpgfx::dpgfx( void )
    {

    }

    //dtor
    dpgfx::~dpgfx( void )
    {

    }

    //generate readlock
    dpshared_readlock *dpgfx::genReadLock( dpmutex_readlock *ml )
    {
        return new dpgfx_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpgfx::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpgfx_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpgfx::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpgfx_ref( this, k, t_sync );
    }

    //override to do task execution
    void dpgfx::onTaskRun( dpthread_writelock *thd, dptask_writelock *tl )
    {

    }

    //override to do task startup
    void dpgfx::onTaskStart( dpthread_writelock *thd, dptask_writelock *tl )
    {

    }

    //override to do task shutdown
    void dpgfx::onTaskStop( dpthread_writelock *thd, dptask_writelock *tl )
    {

    }

}






