
/*

*/

#ifndef dprender_h
#define dprender_h

#include "../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dprender_writelock;

    class dprender : public dptask
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
        virtual void onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual void onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual void onTaskStop( dptask_writelock *tl );

    public:

        //ctor
        dprender( dpapi_factory *wf );
        //dtor
        virtual ~dprender( void );

        friend class dprender_writelock;
        friend class dprender_readlock;
    };

}

#endif






