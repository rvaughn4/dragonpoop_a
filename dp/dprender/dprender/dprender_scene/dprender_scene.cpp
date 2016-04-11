
/*

*/

#include "dprender_scene.h"
#include "dprender_scene_ref.h"
#include "dprender_scene_readlock.h"
#include "dprender_scene_writelock.h"
#include "../../dpapi/dpapi/dpapi_primary_commandlist/dpapi_primary_commandlist_writelock.h"
#include "../../dpapi/dpapi/dpapi_commandlist/dpapi_commandlist.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context.h"
#include "../../dpapi/dpapi/dpapi_context/dpapi_context_writelock.h"
#include "../../dpapi/dpapi/dpapi/dpapi_writelock.h"
#include "../../dpapi/dpapi/dpapi/dpapi_ref.h"
#include "../../dpapi/dpapi/dpapi/dpapi.h"
#include "../dprender/dprender_writelock.h"
#include "../dprender/dprender_ref.h"
#include "../dprender/dprender.h"
#include "../dprender_scene_thread/dprender_scene_thread.h"
#include "../dprender_gui_thread/dprender_gui_thread.h"
#include "../dprender_hello_triangle_scene_thread/dprender_hello_triangle_scene_thread.h"
#include "../../../dpgfx/dpscene/dpscene.h"
#include "../../../dpgfx/dpscene/dpscene_ref.h"

#include <string.h>

namespace dp
{

    //ctor
    dprender_scene::dprender_scene( dpscene *scn, dpapi *api, dprender *r ) : dptask( "Render Scene", 1000 )
    {
        this->apir = (dpapi_ref *)this->g.getRef( api );
        this->rr = (dprender_ref *)this->g.getRef( r );
        this->scn = (dpscene_ref *)this->g.getRef( scn );
        this->zeroTasks();
    }

    //dtor
    dprender_scene::~dprender_scene( void )
    {
        this->waitForStop();
        this->unlink();
        this->deleteTasksAndContexts();
    }

    //generate readlock
    dpshared_readlock *dprender_scene::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_scene_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender_scene::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_scene_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender_scene::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_scene_ref( this, k, t_sync );
    }

    //override to do task execution
    bool dprender_scene::onTaskRun( dptask_writelock *tl )
    {
        return 1;
    }

    //override to do task startup
    bool dprender_scene::onTaskStart( dptask_writelock *tl )
    {
        dpapi_writelock *apil;
        dpshared_guard g;

        apil = (dpapi_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->apir, 1000 );
        if( !apil )
            return 0;

        if( !this->makeContexts( apil ) )
            return 0;

        if( !this->makeTasks( (dprender_scene_writelock *)tl ) )
            return 0;

        return 1;
    }

    //override to do task shutdown
    bool dprender_scene::onTaskStop( dptask_writelock *tl )
    {
        if( !this->stopTasks() )
            return 0;
        this->deleteTasksAndContexts();
        return 1;
    }

    //generate gui task
    dprender_scene_thread *dprender_scene::makeGuiTask( dprender_scene_writelock *l, dpapi_context *ctx, dpapi_commandlist *cl_a, dpapi_commandlist *cl_b, std::atomic<bool> *flag_a, std::atomic<bool> *flag_b )
    {
        return new dprender_gui_thread( this->scn, ctx, cl_a, cl_b, flag_a, flag_b );
    }

    //zero tasks
    void dprender_scene::zeroTasks( void )
    {
        unsigned int i;
        dprender_scene_task *p;

        for( i = 0; i < 5; i++ )
        {
            p = &this->tasks.tsks[ i ];
            p->tsk = 0;
            p->ctx = 0;
            p->a.b = 0;
            p->a.cl = 0;
            p->b.b = 0;
            p->b.cl = 0;
            p->pnext = &p->a;
            p->pprev = &p->b;
        }
    }

    //delete tasks and contexts
    void dprender_scene::deleteTasksAndContexts( void )
    {
        unsigned int i;
        dprender_scene_task *p;

        for( i = 0; i < 5; i++ )
        {
            p = &this->tasks.tsks[ i ];

            if( p->tsk )
                delete p->tsk;
            if( p->a.cl )
                delete p->a.cl;
            if( p->b.cl )
                delete p->b.cl;
            if( p->ctx )
                delete p->ctx;
        }

        this->zeroTasks();
    }

    //make contexts
    bool dprender_scene::makeContexts( dpapi_writelock *apil )
    {
        unsigned int i;
        dprender_scene_task *p;
        dpshared_guard g;
        dpapi_context_writelock *ctxl;

        for( i = 0; i < 5; i++ )
        {
            p = &this->tasks.tsks[ i ];
            p->ctx = apil->makeContext();
            if( !p->ctx )
                return 0;

            ctxl = (dpapi_context_writelock *)dpshared_guard_tryWriteLock_timeout( g, p->ctx, 1000 );
            if( !ctxl )
                return 0;

            p->a.cl = ctxl->makeCommandList();
            if( !p->a.cl )
                return 0;

            p->b.cl = ctxl->makeCommandList();
            if( !p->b.cl )
                return 0;
        }

        return 1;
    }

    //make tasks
    bool dprender_scene::makeTasks( dprender_scene_writelock *l )
    {
        dprender_scene_task *p;

        p = &this->tasks.tskname.gui_task;
        p->tsk = this->makeGuiTask( l, p->ctx, p->a.cl, p->b.cl, &p->a.b, &p->b.b );
        if( p->tsk )
        {
            if( !this->addStaticTask( p->tsk, 1 ) )
                return 0;
        }

        return 1;
    }

    //draw scene
    bool dprender_scene::draw( dprender_scene_writelock *rl, dpapi_context_writelock *ctxl, dpapi_primary_commandlist_writelock *cll )
    {
        dprender_scene_task *t;
        dprender_scene_task_inner *c;

        t = &this->tasks.tskname.gui_task;
        if( !t->pnext->b )
            return 0;
        cll->addCommandList( ctxl, t->pnext->cl );
        t->pnext->b = 0;
        c = t->pnext;
        t->pnext = t->pprev;
        t->pprev = c;

        return 1;
    }

    //purge tasks and all api stuff so that api can be deleted
    void dprender_scene::purgeAll( void )
    {
        this->deleteTasksAndContexts();
    }

    //stop tasks, or return zero if task not stopped
    bool dprender_scene::stopTasks( void )
    {
        unsigned int i;
        dprender_scene_task *p;
        dpshared_guard g;
        dptask_writelock *l;
        bool r;

        r = 1;
        for( i = 0; i < 5; i++ )
        {
            p = &this->tasks.tsks[ i ];
            if( !p->tsk )
                continue;

            l = (dptask_writelock *)dpshared_guard_tryWriteLock_timeout( g, p->tsk, 100 );
            if( !l )
            {
                r = 0;
                continue;
            }

            if( !l->isRun() )
                continue;

            r = 0;
            l->stop();
        }

        return r;
    }

    //returns true if belongs to scene
    bool dprender_scene::hasScene( dpscene *scn )
    {
        if( !this->scn )
            return 0;
        return this->scn->isParent( scn );
    }

}








