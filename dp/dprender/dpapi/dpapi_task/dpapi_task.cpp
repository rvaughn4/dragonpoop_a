
/*
*/

#include "dpapi_task.h"
#include "../dpapi/dpapi/dpapi.h"
#include "../dpapi/dpapi/dpapi_writelock.h"
#include "../dpapi/dpapi/dpapi_factory.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"

class dpapi;
class dpapi_factory;

namespace dp
{

    //ctor
    dpapi_task::dpapi_task( dpapi_factory *wf ) : dptask( "api task", 100 )
    {
        this->wf = wf;
    }

    //dtor
    dpapi_task::~dpapi_task( void )
    {
        this->waitForStop();
        delete this->wf;
    }

    //override to do task execution
    bool dpapi_task::onTaskRun( dptask_writelock *tl )
    {
        dpapi_writelock *l;
        dpshared_guard g;

        l = (dpapi_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->w, 1000 );
        if( !l )
            return 0;

        l->run();

        return l->isOpen();
    }

    //override to do task startup
    bool dpapi_task::onTaskStart( dptask_writelock *tl )
    {
        this->w = this->wf->makeApi();
        return this->w != 0;
    }

    //override to do task shutdown
    bool dpapi_task::onTaskStop( dptask_writelock *tl )
    {
        delete this->w;
        return 1;
    }

}






