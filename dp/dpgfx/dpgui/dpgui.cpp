
/*
*/

#include "dpgui.h"
#include "dpgui_ref.h"
#include "dpgui_readlock.h"
#include "dpgui_writelock.h"
#include "../dpfont/dpfont/dpfont.h"

namespace dp
{

    //ctor
    dpgui::dpgui( int x, int y, unsigned w, unsigned h, const char *ctxt ) : dpgui_list()
    {
        this->bBgDrawn = 0;
        this->bFgDrawn = 0;

        this->rc.x = x;
        this->rc.y = y;
        this->rc.w = w;
        this->rc.h = h;

        this->bm_bg = 0;
        this->bm_fg = 0;
        this->sz_time = this->bg_time = this->fg_time = 0;

        this->setText( ctxt );
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

            this->bm_bg->clear();

            this->renderBackgroundPass0( this->bm_bg );
            this->renderBackgroundPass1( this->bm_bg );

            this->bg_time++;
            this->bBgDrawn = 1;
            this->update();
        }

        if( !this->bFgDrawn )
        {
            if( this->bm_fg )
                delete this->bm_fg;
            this->bm_fg = new dpbitmap_32bit_uncompressed( this->rc.w, this->rc.h );

            this->bm_fg->clear();

            this->renderForegroundPass0( this->bm_fg );
            this->renderForegroundPass1( this->bm_fg );

            this->fg_time++;
            this->bFgDrawn = 1;
            this->update();
        }

        return this->dpgui_list::onTaskRun( tl );
    }

    //override to do task startup
    bool dpgui::onTaskStart( dptask_writelock *tl )
    {
        if( !this->onGuiStart( (dpgui_writelock *)tl ) )
            return 0;
        return this->dpgui_list::onTaskStart( tl );
    }

    //override to do task shutdown
    bool dpgui::onTaskStop( dptask_writelock *tl )
    {
        if( !this->onGuiStop( (dpgui_writelock *)tl ) )
            return 0;
        return this->dpgui_list::onTaskStop( tl );
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
        this->renderText( bm );
    }

    //render text
    void dpgui::renderText( dpbitmap *bm )
    {
        dpfont fnt;
        dpbitmap_color c;

        c.r = 0;
        c.g = 0;
        c.b = 0;
        c.a = 1;

        fnt.setColor( &c );
        fnt.setSize( 100 );
        fnt.openFont( "sans" );

        fnt.drawString( &this->stxt, 0, 0, bm );
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
        this->sz_time++;
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

    //return z
    unsigned int dpgui::getZ( void )
    {
        return this->z;
    }

    //set z
    void dpgui::setZ( unsigned int z )
    {
        this->z = z;
    }

    //override to handle sync copy, be sure to call base class first!
    void dpgui::onSync( dpshared_readlock *psync )
    {
        this->dpgui_list::onSync( psync );
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dpgui::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( s.compare( "dpgui" ) == 0 )
            return 1;

        return this->dpgui_list::isSyncType( ctypename );
    }

    //returns bg bitmap
    dpbitmap *dpgui::getBg( void )
    {
        return this->bm_bg;
    }

    //returns fg bitmap
    dpbitmap *dpgui::getFg( void )
    {
        return this->bm_fg;
    }

    //set text
    void dpgui::setText( const char *ctxt )
    {
        this->stxt.assign( ctxt );
        this->redrawFg();
    }

    //get text
    void dpgui::getText( std::string *s )
    {
        s->assign( this->stxt );
    }

    //return bg time
    unsigned int dpgui::getBgTime( void )
    {
        return this->bg_time;
    }

    //return fg time
    unsigned int dpgui::getFgTime( void )
    {
        return this->fg_time;
    }

    //return size time
    unsigned int dpgui::getSzTime( void )
    {
        return this->sz_time;
    }

}





