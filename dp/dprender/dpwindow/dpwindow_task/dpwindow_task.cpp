
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
    bool dpwindow_task::onTaskRun( dptask_writelock *tl )
    {
        dpwindow_writelock *l;
        dpshared_guard g;

        l = (dpwindow_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->w, 1000 );
        if( !l )
            return 0;

        l->run();

        return l->isOpen();
    }

    //override to do task startup
    bool dpwindow_task::onTaskStart( dptask_writelock *tl )
    {
        this->w = this->wf->makeWindow();
        return this->w != 0;
    }

    //override to do task shutdown
    bool dpwindow_task::onTaskStop( dptask_writelock *tl )
    {
        delete this->w;
        return 1;
    }

}





