/*

*/

#ifndef dpscene_h
#define dpscene_h

#include "../../dpcore/dptask/dptask.h"

namespace dp
{
    class dpscene_writelock;
    class dpgui;
    class dpgfx;
    class dpgfx_ref;

    class dpscene : public dptask
    {

    private:

        dpgui *root_gui;
        dpgfx_ref *pgfx;
        dpshared_guard g;

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //override to do task execution
        virtual bool onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual bool onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual bool onTaskStop( dptask_writelock *tl );
        //override to handle sync copy, be sure to call base class first!
        virtual void onSync( dpshared_readlock *psync );
        //override to test type for safe syncing, be sure to call base class first!
        virtual bool isSyncType( const char *ctypename );
        //override to handle scene start
        virtual bool onSceneStart( dpscene_writelock *sl );
        //override to handle scene stop
        virtual bool onSceneStop( dpscene_writelock *sl );
        //override to handle scene run
        virtual bool onSceneRun( dpscene_writelock *sl );
        //return root gui
        dpgui *getGui( void );
        //generate root gui
        virtual dpgui *genRootGui( dpscene_writelock *sl );
        //attach scene
        void attach( dpgfx *g );
        //add scene
        bool addScene( dpscene **s );

    public:

        //ctor
        dpscene( void );
        //dtor
        virtual ~dpscene( void );

        friend class dpscene_writelock;
        friend class dpscene_readlock;
    };

};

#endif
