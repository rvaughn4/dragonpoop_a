
/*
*/

#ifndef dpgui_h
#define dpgui_h

#include "../dpgui_list/dpgui_list.h"
#include "../dpbitmap/dpbitmap/dpbitmap.h"
#include "../dpbitmap/dpbitmap_32bit_uncompressed/dpbitmap_32bit_uncompressed.h"

namespace dp
{

    class dpgui_writelock;

    class dpgui : public dpgui_list
    {

    private:

        dpbitmap_rectangle rc;
        dpbitmap_32bit_uncompressed *bm_bg, *bm_fg;
        bool bBgDrawn, bFgDrawn;
        unsigned int z;

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
        //set dimensions
        virtual void setDimensions( unsigned int w, unsigned int h );
        //set position
        virtual void setPosition( int x, int y );
        //get dimensions
        virtual void getDimensions( unsigned int *w, unsigned int *h );
        //get position
        virtual void getPosition( int *x, int *y );
        //force bg to be redrawn
        virtual void redrawBg( void );
        //force fg to be redrawn
        virtual void redrawFg( void );

    public:

        //ctor
        dpgui( int x, int y, unsigned w, unsigned h );
        //dtor
        virtual ~dpgui( void );
        //return z
        virtual unsigned int getZ( void );
        //set z
        virtual void setZ( unsigned int z );

        friend class dpgui_writelock;
        friend class dpgui_readlock;
    };

}

#endif




