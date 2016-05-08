
/*
*/

#include "dpgui.h"
#include "dpgui_ref.h"
#include "dpgui_readlock.h"
#include "dpgui_writelock.h"
#include "../dpfont/dpfont/dpfont.h"
#include "../../dprender/dpinput/dpinput.h"
#include "../../dprender/dpinput/dpinput_readlock.h"
#include "../../dprender/dpinput/dpinput_writelock.h"

#include <iostream>

namespace dp
{

    //ctor
    dpgui::dpgui( int x, int y, unsigned int w, unsigned int h, const char *ctxt ) : dpgui_list()
    {
        this->bBgDrawn = 0;
        this->bFgDrawn = 0;
        this->bRedrawOnResize = 0;

        this->rc.x = x;
        this->rc.y = y;
        this->rc.w = w;
        this->rc.h = h;

        this->bm_bg = 0;
        this->bm_fg = 0;
        this->sz_time = this->bg_time = this->fg_time = 0;

        this->setText( ctxt );

        this->t_input = 0;
        this->inp = new dpinput();

        this->bFollowCursor = 0;
        this->bIsCentered = 0;
        this->bIsFloating = 0;
        this->bGrows = 0;
        this->zoom = 1.0f;
        this->bFillHoriz = 0;

        this->rot.x = this->rot.y = this->rot.z = 0;
        this->spin = this->rot;

        this->bBorderInvert = 0;
        this->border_sz = 2;
        this->fnt_sz = h * 3 / 5;

        this->bg_clr.r = 1.0f;
        this->bg_clr.g = 1.0f;
        this->bg_clr.b = 1.0f;
        this->bg_clr.a = 0.75f;

        this->fnt_clr.r = 0.0f;
        this->fnt_clr.g = 0.0f;
        this->fnt_clr.b = 0.0f;
        this->fnt_clr.a = 1.0f;

        this->cursor = 0;
        this->select_start = 0;
        this->select_end = 0;
    }

    //dtor
    dpgui::~dpgui( void )
    {
        if( this->bm_bg )
            delete this->bm_bg;
        if( this->bm_fg )
            delete this->bm_fg;
        if( this->inp )
            delete this->inp;
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

    //run input
    void dpgui::runInput( void )
    {
        dpinput_readlock *irl;
        dpinput_writelock *iwl;
        dpshared_guard g;
        dpinput_event *elist[ 100 ], *p;
        unsigned int i, j;

        iwl = (dpinput_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->inp, 30 );
        if( !iwl )
            return;
        iwl->run();
        g.release( iwl );

        irl = (dpinput_readlock *)dpshared_guard_tryReadLock_timeout( g, this->inp, 30 );
        if( !irl )
            return;

        j = irl->getEvents( elist, 100, this->t_input );
        this->t_input = this->getTicks();

        for( i = 0; i < j; i++ )
        {
            p = elist[ i ];
            this->onInput( p );
        }

        g.release( irl );
    }

    //attach renderer input
    void dpgui::attachInput( dpinput *i )
    {
        dpinput_writelock *iwl;
        dpshared_guard g;

        iwl = (dpinput_writelock *)dpshared_guard_tryWriteLock_timeout( g, this->inp, 3000 );
        if( !iwl )
            return;

        iwl->setSync( i );
    }

    //override to do task execution
    bool dpgui::onTaskRun( dptask_writelock *tl )
    {
        if( !this->onGuiRun( (dpgui_writelock *)tl ) )
            return 0;

        this->runInput();

        if( !this->bBgDrawn )
        {
            if( !this->bm_bg || this->bm_bg->getWidth() != (int)this->rc.w || this->bm_bg->getHeight() != (int)this->rc.h )
            {
                delete this->bm_bg;
                this->bm_bg = new dpbitmap_32bit_uncompressed( this->rc.w, this->rc.h );
            }

            this->bm_bg->clear();

            this->renderBackgroundPass0( this->bm_bg );
            this->renderBackgroundPass1( this->bm_bg );

            this->bg_time++;
            this->bBgDrawn = 1;
            this->update();
        }

        if( !this->bFgDrawn )
        {
            if( !this->bm_fg || this->bm_fg->getWidth() != (int)this->rc.w || this->bm_fg->getHeight() != (int)this->rc.h )
            {
                delete this->bm_fg;
                this->bm_fg = new dpbitmap_32bit_uncompressed( this->rc.w, this->rc.h );
            }

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
    void dpgui::renderBackgroundPass0( dpbitmap_32bit_uncompressed *bm )
    {
        bm->fill( &this->bg_clr );
    }

    //render second pass of background image
    void dpgui::renderBackgroundPass1( dpbitmap_32bit_uncompressed *bm )
    {
        bm->buttonize( this->border_sz, 0.7f, this->bBorderInvert );
    }

    //render first pass of foreground image
    void dpgui::renderForegroundPass0( dpbitmap_32bit_uncompressed *bm )
    {

    }

    //render second pass of foreground image
    void dpgui::renderForegroundPass1( dpbitmap_32bit_uncompressed *bm )
    {
        this->renderText( bm );
    }

    //render text
    void dpgui::renderText( dpbitmap_32bit_uncompressed *bm )
    {
        dpfont fnt;
        dpbitmap_rectangle rc;

        rc.x = 10;
        rc.y = 10;
        rc.w = this->rc.w - 10;
        rc.h = this->rc.h - 10;

        fnt.setColor( &this->fnt_clr );
        fnt.setSize( 12 );
        fnt.openFont( "sans" );

        if( !fnt.setSize( this->fnt_sz ) )
            fnt.setSize( 12 );

        fnt.setCursor( this->cursor );
        fnt.setSelection( this->select_start, this->select_end );

        fnt.drawString( this->ctxt, dpgui_max_locs, &rc, 0, bm, this->char_locs, dpgui_max_locs );
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
        if( this->bRedrawOnResize )
        {
            this->bBgDrawn = 0;
            this->bFgDrawn = 0;
        }
        this->sz_time++;
    }

    //set position
    void dpgui::setPosition( int x, int y )
    {
        this->rc.x = x;
        this->rc.y = y;
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
    dpbitmap_32bit_uncompressed *dpgui::getBg( void )
    {
        return this->bm_bg;
    }

    //returns fg bitmap
    dpbitmap_32bit_uncompressed *dpgui::getFg( void )
    {
        return this->bm_fg;
    }

    //set text
    void dpgui::setText( const char *ctxt )
    {
        std::string s;

        s.assign( ctxt );
        memset( this->ctxt, 0, dpgui_max_locs );
        s.copy( this->ctxt, dpgui_max_locs );
        this->sz = s.length();

        this->redrawFg();
    }

    //get text
    void dpgui::getText( std::string *s )
    {
        s->assign( this->ctxt );
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

    //override to handle input events
    void dpgui::onInput( dpinput_event *e )
    {
        switch( e->h.etype )
        {
        case dpinput_event_type_mouse:
            this->onMouseMove( &e->mse );
            break;
        case dpinput_event_type_leftclick:
            this->onLeftClick( &e->mse );
            break;
        case dpinput_event_type_rightclick:
            this->onRightClick( &e->mse );
            break;
        case dpinput_event_type_keypress:
            if( e->keyp.bIsDown )
                this->onKeyDown( &e->keyp );
            else
                this->onKeyUp( &e->keyp );
            break;
        case dpinput_event_type_text:
            this->onText( &e->txt );
            break;
        }
    }

    //override to handle left clicks
    void dpgui::onLeftClick( dpinput_event_mouse *e )
    {
        this->setCursor( this->findLoc( e->x, e->y ) );
        this->redrawFg();
    }

    //override to handle right clicks
    void dpgui::onRightClick( dpinput_event_mouse *e )
    {

    }

    //override to handle mouse movement
    void dpgui::onMouseMove( dpinput_event_mouse *e )
    {

    }

    //override to handle key press down
    void dpgui::onKeyDown( dpinput_event_keypress *e )
    {
        std::string s;

        s.assign( e->keyName );

        if( s.compare( "Shift" ) == 0 )
            this->bShiftDown = 1;
    }

    //override to handle key press up
    void dpgui::onKeyUp( dpinput_event_keypress *e )
    {
        std::string s;

        s.assign( e->keyName );

        if( s.compare( "Shift" ) == 0 )
            this->bShiftDown = 0;
        if( s.compare( "Left" ) == 0 )
        {
            this->moveCursorLeft();
            this->redrawFg();
        }
        if( s.compare( "Right" ) == 0 )
        {
            this->moveCursorRight();
            this->redrawFg();
        }
        if( s.compare( "Up" ) == 0 )
        {
            this->moveCursorUp();
            this->redrawFg();
        }
        if( s.compare( "Down" ) == 0 )
        {
            this->moveCursorDown();
            this->redrawFg();
        }
        if( s.compare( "Delete" ) == 0 )
        {
            this->deleteAtCursor();
            this->redrawFg();
        }
        if( s.compare( "Backspace" ) == 0 )
        {
            this->backspace();
            this->redrawFg();
        }
    }

    //override to handle text input
    void dpgui::onText( dpinput_event_text *e )
    {

    }

    //return true if centered
    bool dpgui::isCentered( void )
    {
        return this->bIsCentered;
    }

    //set centered mode
    void dpgui::setCentered( bool b )
    {
        this->bIsCentered = b;
    }

    //return true if floating
    bool dpgui::isFloating( void )
    {
        return this->bIsFloating;
    }

    //set floating mode
    void dpgui::setFloating( bool b )
    {
        this->bIsFloating = b;
    }

    //return true if follows cursor
    bool dpgui::isFollowingCursor( void )
    {
        return this->bFollowCursor;
    }

    //set cursor following mode
    void dpgui::setFollowingCursor( bool b )
    {
        this->bFollowCursor = b;
    }

    //get rotation
    void dpgui::getRotation( dpxyzw *p )
    {
        *p = this->rot;
    }

    //set rotation
    void dpgui::setRotation( dpxyzw *p )
    {
        this->rot = *p;
    }

    //get spin
    void dpgui::getSpin( dpxyzw *p )
    {
        *p = this->spin;
    }

    //set spin
    void dpgui::setSpin( dpxyzw *p )
    {
        this->spin = *p;
    }

    //returns true if grows when mouse hovers over
    bool dpgui::doesGrow( void )
    {
        return this->bGrows;
    }

    //set mouse hover mode
    void dpgui::setGrow( bool b )
    {
        this->bGrows = b;
    }

    //returns true if minimized
    bool dpgui::isMinimized( void )
    {
        return this->bMin;
    }

    //set minimized
    void dpgui::setMinimized( bool b )
    {
        this->bMin = b;
    }

    //set alignment
    void dpgui::setAlignment( unsigned int a )
    {
        this->align = a;
    }

    //get alignment
    unsigned int dpgui::getAlignment( void )
    {
        return this->align;
    }

    //set background color
    void dpgui::setBgColor( dpbitmap_color *c )
    {
        this->bg_clr = *c;
    }

    //set font color
    void dpgui::setFontColor( dpbitmap_color *c )
    {
        this->fnt_clr = *c;
    }

    //set border width
    void dpgui::setBorderWidth( unsigned int w )
    {
        this->border_sz = w;
    }

    //set font size
    void dpgui::setFontSize( unsigned int s )
    {
        this->fnt_sz = s;
    }

    //set border inverted
    void dpgui::setBorderInverted( bool b )
    {
        this->bBorderInvert = b;
    }

    //set zoom
    void dpgui::setZoom( float z )
    {
        if( z < 0.3f )
            z = 0.3f;
        this->zoom = z;
    }

    //get zoom
    float dpgui::getZoom( void )
    {
        return this->zoom;
    }

    //zoom in
    void dpgui::zoomIn( void )
    {
        this->setZoom( this->zoom * 1.1f );
    }

    //zoom out
    void dpgui::zoomOut( void )
    {
        this->setZoom( this->zoom * 0.9f );
    }

    //set horizontal auto-fill/stretch
    void dpgui::setHorizFill( bool b )
    {
        this->bFillHoriz = b;
    }

    //returns true if horiz fill enabled
    bool dpgui::isHorizFill( void )
    {
        return this->bFillHoriz;
    }

    //find location in text
    unsigned int dpgui::findLoc( int x, int y )
    {
        unsigned int i, r;
        dpbitmap_rectangle *p;

        r = dpgui_max_locs;
        for( i = 0; i < dpgui_max_locs; i++ )
        {
            p = &this->char_locs[ i ];

            if( x < p->x || y < p->y )
                continue;
            if( x > p->x + (int)p->w + (int)p->w || y > p->y + (int)p->h + (int)p->h )
                continue;
            r = i;
        }

        return r;
    }

    //set cursor
    void dpgui::setCursor( unsigned int c )
    {
        unsigned int m, i, j;
        dpbitmap_rectangle *r;

        m = this->sz;
        if( m >= dpgui_max_locs )
            m = dpgui_max_locs - 1;
        if( c >= m )
            c = m;

        j = i = 0;
        if( c > 50 )
            i = c - 50;

        for( ; i <= c; i++ )
        {
            r = &this->char_locs[ i ];
            if( r->w == 0 )
                continue;
            j = i;
        }

        this->cursor = j;

        if( !this->bShiftDown )
            this->select_start = this->select_end = this->cursor;
        else
        {
            if( this->cursor < this->select_start )
                this->select_start = this->cursor;
            if( this->cursor > this->select_end )
                this->select_end = this->cursor;
        }
    }

    //move cursor left
    void dpgui::moveCursorLeft( void )
    {
        unsigned int c;

        c = this->cursor;
        if( c > 0 )
            c--;

        this->setCursor( c );
    }

    //move cursor right
    void dpgui::moveCursorRight( void )
    {
        unsigned int m, i, j, c;
        dpbitmap_rectangle *r;

        m = this->sz;
        if( m >= dpgui_max_locs )
            m = dpgui_max_locs - 1;
        if( c > m )
            c = m;

        c = this->cursor + 1;
        j = c + 50;
        if( j > m )
            j = m;
        if( j >= dpgui_max_locs )
            j = dpgui_max_locs - 1;

        for( i = j; i >= c; i-- )
        {
            r = &this->char_locs[ i ];
            if( r->w == 0 )
                continue;
            m = i;
        }

        this->setCursor( m );
    }

    //move cursor down
    void dpgui::moveCursorDown( void )
    {
        int x, y;
        dpbitmap_rectangle *p;

        if( this->cursor >= dpgui_max_locs )
            return;

        p = &this->char_locs[ this->cursor ];
        x = p->x;
        y = p->y + p->h + 3;

        this->setCursor( this->findLoc( x, y ) );
    }

    //move cursor up
    void dpgui::moveCursorUp( void )
    {
        int x, y;
        dpbitmap_rectangle *p;

        if( this->cursor >= dpgui_max_locs )
            return;

        p = &this->char_locs[ this->cursor ];
        x = p->x;
        y = p->y - p->h + 3;

        this->setCursor( this->findLoc( x, y ) );
    }

    //delete text at cursor or selection, implemented as insert empty string
    void dpgui::deleteAtCursor( void )
    {
        if( this->select_start >= this->select_end )
        {
            this->select_start = this->cursor;
            this->select_end = this->cursor + 1;
        }

        this->insertText( "" );
    }

    //insert text at cursor or selection, clears selection and puts cursor at end
    void dpgui::insertText( const char *c )
    {
        std::string so, sc;

        so.assign( this->ctxt );
        sc.assign( c );

        if( (int)this->cursor >= (int)so.length() )
            this->cursor = so.length();

        if( (int)this->select_end > (int)so.length() )
            this->select_end = so.length();
        if( this->select_start > this->select_end )
            this->select_start = this->select_end;

        if( this->select_start < this->select_end )
        {
            so.erase( this->select_start, this->select_end - this->select_start );
            this->cursor = this->select_end = this->select_start;
            if( (int)this->cursor >= (int)so.length() )
                this->cursor = so.length();
        }

        so.insert( this->cursor, sc );
        this->cursor += sc.length();

        this->setText( so.c_str() );
    }

    //backspace, implemented as move cursor left one then call delete
    void dpgui::backspace( void )
    {
        if( this->select_start >= this->select_end && this->cursor > 0 )
            this->cursor -= 1;
        this->deleteAtCursor();
    }

}





