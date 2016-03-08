
/*

*/

#include "dprender.h"
#include "dprender_ref.h"
#include "dprender_readlock.h"
#include "dprender_writelock.h"
#include "../../dpapi/dpapi/dpapi/dpapi_factory.h"
#include "../../dpapi/dpapi/dpapi/dpapi.h"

namespace dp
{

    //ctor
    dprender::dprender( dpapi_factory *wf ) : dptask( "Renderer Main", 30 )
    {
        this->apifactory = wf;
        this->api = 0;
    }

    //dtor
    dprender::~dprender( void )
    {
        if( this->api )
            delete this->api;
        delete this->apifactory;
    }

    //generate readlock
    dpshared_readlock *dprender::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_ref( this, k, t_sync );
    }

    //override to do task execution
    void dprender::onTaskRun( dptask_writelock *tl )
    {

    }

    //override to do task startup
    void dprender::onTaskStart( dptask_writelock *tl )
    {

    }

    //override to do task shutdown
    void dprender::onTaskStop( dptask_writelock *tl )
    {

    }

}







