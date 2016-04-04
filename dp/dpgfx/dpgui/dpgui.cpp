
/*
*/

#include "dpgui.h"
#include "dpgui_ref.h"
#include "dpgui_readlock.h"
#include "dpgui_writelock.h"

namespace dp
{

    //ctor
    dpgui::dpgui( int x, int y, unsigned w, unsigned h ) : dptask( "gui", 500 )
    {
        this->bBgDrawn = 0;
        this->bFgDrawn = 0;

        this->rc.x = x;
        this->rc.y = y;
        this->rc.w = w;
        this->rc.h = h;

        this->bm_bg = 0;
        this->bm_fg = 0;
    }

    //dtor
    dpgui::~dpgui( void )
    {
        if( this->bm_bg )
            delete this->bm_bg;
        if( this->bm_fg )
            delete this->bm_fg;
    }

    //generate readlock
    dpshared_readlock *dpgui::genReadLock( dpmutex_readlock *ml )
    {
        return new dpgui_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpgui::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpgui_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpgui::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpgui_ref( this, k, t_sync );
    }

    //override to do task execution
    bool dpgui::onTaskRun( dptask_writelock *tl )
    {
        if( !this->onGuiRun( (dpgui_writelock *)tl ) )
            return 0;

        if( !this->bBgDrawn )
        {
            if( this->bm_bg )
                delete this->bm_bg;
            this->bm_bg = new dpbitmap_32bit_uncompressed( this->rc.w, this->rc.h );

            this->renderBackgroundPass0( this->bm_bg );
            this->renderBackgroundPass1( this->bm_bg );

            this->bBgDrawn = 1;
        }

        if( !this->bFgDrawn )
        {
            if( this->bm_fg )
                delete this->bm_fg;
            this->bm_fg = new dpbitmap_32bit_uncompressed( this->rc.w, this->rc.h );

            this->renderForegroundPass0( this->bm_fg );
            this->renderForegroundPass1( this->bm_fg );

            this->bFgDrawn = 1;
        }

        return 1;
    }

    //override to do task startup
    bool dpgui::onTaskStart( dptask_writelock *tl )
    {
        return this->onGuiStart( (dpgui_writelock *)tl );
    }

    //override to do task shutdown
    bool dpgui::onTaskStop( dptask_writelock *tl )
    {
        return this->onGuiStop( (dpgui_writelock *)tl );
    }

    //render first pass background image
    void dpgui::renderBackgroundPass0( dpbitmap *bm )
    {

    }

    //render second pass of background image
    void dpgui::renderBackgroundPass1( dpbitmap *bm )
    {

    }

    //render first pass of foreground image
    void dpgui::renderForegroundPass0( dpbitmap *bm )
    {

    }

    //render second pass of foreground image
    void dpgui::renderForegroundPass1( dpbitmap *bm )
    {

    }

    //override to handle gui ran
    bool dpgui::onGuiRun( dpgui_writelock *tl )
    {
        return 1;
    }

    //override to handle gui start
    bool dpgui::onGuiStart( dpgui_writelock *tl )
    {
        return 1;
    }

    //override to handle gui stop
    bool dpgui::onGuiStop( dpgui_writelock *tl )
    {
        return 1;
    }

    //set dimensions
    void dpgui::setDimensions( unsigned int w, unsigned int h )
    {
        this->rc.w = w;
        this->rc.h = h;
        this->update();
    }

    //set position
    void dpgui::setPosition( int x, int y )
    {
        this->rc.x = x;
        this->rc.y = y;
        this->update();
    }

    //get dimensions
    void dpgui::getDimensions( unsigned int *w, unsigned int *h )
    {
        *w = this->rc.w;
        *h = this->rc.h;
    }

    //get position
    void dpgui::getPosition( int *x, int *y )
    {
        *x = this->rc.x;
        *y = this->rc.y;
    }

    //force bg to be redrawn
    void dpgui::redrawBg( void )
    {
        this->bBgDrawn = 0;
    }

    //force fg to be redrawn
    void dpgui::redrawFg( void )
    {
        this->bFgDrawn = 0;
    }

}





