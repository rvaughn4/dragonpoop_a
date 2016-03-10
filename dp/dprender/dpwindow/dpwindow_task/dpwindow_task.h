
/*
*/

#ifndef dpwindow_task_h
#define dpwindow_task_h

#include "../../../dpcore/dptask/dptask.h"


namespace dp
{

    class dpwindow;
    class dpwindow_factory;

    class dpwindow_task : public dptask
    {

    private:

        dpwindow_factory *wf;
        dpwindow *w;

    protected:

        //override to do task execution
        virtual bool onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual bool onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual bool onTaskStop( dptask_writelock *tl );

    public:

        //ctor
        dpwindow_task( dpwindow_factory *wf );
        //dtor
        virtual ~dpwindow_task( void );

    };

}

#endif




