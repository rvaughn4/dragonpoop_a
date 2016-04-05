
/*
*/

#include "dprender_gui.h"
#include "dprender_gui_ref.h"
#include "dprender_gui_readlock.h"
#include "dprender_gui_writelock.h"
#include "../../../dpgfx/dpgui/dpgui.h"
#include "../../../dpgfx/dpgui/dpgui_readlock.h"

namespace dp
{

    //ctor
    dprender_gui::dprender_gui( dpgui *pg ) : dprender_gui_list()
    {
        this->setSync( pg );

        this->t_bg = this->t_fg = 0;
        this->vb = 0;
        this->ib_bg = this->ib_fg = 0;
    }

    //dtor
    dprender_gui::~dprender_gui( void )
    {
    }

    //generate readlock
    dpshared_readlock *dprender_gui::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_gui_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender_gui::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_gui_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender_gui::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_gui_ref( this, k, t_sync );
    }

    //set dimensions
    void dprender_gui::setDimensions( unsigned int w, unsigned int h )
    {
        this->rc.w = w;
        this->rc.h = h;
    }

    //set position
    void dprender_gui::setPosition( int x, int y )
    {
        this->rc.x = x;
        this->rc.y = y;
    }

    //get dimensions
    void dprender_gui::getDimensions( unsigned int *w, unsigned int *h )
    {
        *w = this->rc.w;
        *h = this->rc.h;
    }

    //get position
    void dprender_gui::getPosition( int *x, int *y )
    {
        *x = this->rc.x;
        *y = this->rc.y;
    }

    //return z
    unsigned int dprender_gui::getZ( void )
    {
        return this->z;
    }

    //set z
    void dprender_gui::setZ( unsigned int z )
    {
        this->z = z;
    }

    //override to handle sync copy, be sure to call base class first!
    void dprender_gui::onSync( dpshared_readlock *psync )
    {
        dpgui_readlock *gr;

        this->dprender_gui_list::onSync( psync );

        if( !psync->isSyncType( "dpgui" ) )
            return;
        gr = (dpgui_readlock *)psync;

        if( this->blde )
            delete this->bdle;
        if( this->ib_bg )
            delete this->ib_bg;
        if( this->ib_fg )
            delete this->ib_fg;
        if( this->vb )
            //delete



        gr->getDimensions( &this->rc.w, &this->rc.h );
        gr->getPosition( &this->rc.x, &this->rc.y );
        this->z = gr->getZ();
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dprender_gui::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( s.compare( "dprender_gui" ) == 0 )
            return 1;

        return this->dprender_gui_list::isSyncType( ctypename );
    }

    //override to handle processing
    void dprender_gui::onRun( dpshared_writelock *wl )
    {
        this->dprender_gui_list::onRun( wl );
    }

    //pass in context
    void dprender_gui::passContext( dpapi_context_writelock *ctx )
    {
        this->ctx = ctx;
        this->dprender_gui_list::passContext( ctx );
    }

}






