
/*
*/

#ifndef dpapi_task_h
#define dpapi_task_h

#include "../../../dpcore/dptask/dptask.h"


namespace dp
{

    class dpapi;
    class dpapi_factory;

    class dpapi_task : public dptask
    {

    private:

        dpapi_factory *wf;
        dpapi *w;

    protected:

        //override to do task execution
        virtual void onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual void onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual void onTaskStop( dptask_writelock *tl );

    public:

        //ctor
        dpapi_task( dpapi_factory *wf );
        //dtor
        virtual ~dpapi_task( void );

    };

}

#endif





