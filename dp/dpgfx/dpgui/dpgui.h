
/*
*/

#ifndef dpgui_h
#define dpgui_h

#include "../../dpcore/dptask/dptask.h"

namespace dp
{
    class dpbitmap;

    class dpgui : public dptask
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
        virtual bool onTaskRun( dptask_writelock *tl );
        //override to do task startup
        virtual bool onTaskStart( dptask_writelock *tl );
        //override to do task shutdown
        virtual bool onTaskStop( dptask_writelock *tl );
        //render first pass background image
        virtual void renderBackgroundPass0( dpbitmap *bm );
        //render second pass of background image
        virtual void renderBackgroundPass1( dpbitmap *bm );
        //render first pass of foreground image
        virtual void renderForegroundPass0( dpbitmap *bm );
        //render second pass of foreground image
        virtual void renderForegroundPass1( dpbitmap *bm );
        //override to handle gui ran
        virtual bool onGuiRun( dpgui_writelock *tl );
        //override to handle gui start
        virtual bool onGuiStart( dpgui_writelock *tl );
        //override to handle gui stop
        virtual bool onGuiStop( dpgui_writelock *tl );

    public:

        //ctor
        dpgui( void );
        //dtor
        virtual ~dpgui( void );

        friend class dpgui_writelock;
        friend class dpgui_readlock;
    };

}

#endif




