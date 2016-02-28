
/*
*/

#include "dpwindow_task.h"
#include "../dpwindow/dpwindow.h"
#include "../dpwindow/dpwindow_writelock.h"
#include "../dpwindow/dpwindow_factory.h"
#include "../../../dpcore/dpshared/dpshared_guard.h"

class dpwindow;
class dpwindow_factory;

namespace dp
{

    //ctor
    dpwindow_task::dpwindow_task( dpwindow_factory *wf ) : dptask( "window task", 100 )
    {
        this->wf = wf;
    }

    //dtor
    dpwindow_task::~dpwindow_task( void )
    {
        this->waitForStop();
        delete this->wf;
    }

    //override to do task execution
    void dpwindow_task::onTaskRun( dpthread_writelock *thd, dptask_writelock *tl )
    {
        dpwindow_writelock *l;
        dpshared_guard g;

        l = (dpwindow_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->w, 100 );
        if( !l )
            return;

        l->run();
    }

    //override to do task startup
    void dpwindow_task::onTaskStart( dpthread_writelock *thd, dptask_writelock *tl )
    {
        this->w = this->wf->makeWindow();
    }

    //override to do task shutdown
    void dpwindow_task::onTaskStop( dpthread_writelock *thd, dptask_writelock *tl )
    {
        delete this->w;
    }

}





