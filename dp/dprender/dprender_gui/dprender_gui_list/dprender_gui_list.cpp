
/*
*/

#include "dprender_gui_list.h"
#include "dprender_gui_list_ref.h"
#include "dprender_gui_list_readlock.h"
#include "dprender_gui_list_writelock.h"
#include "../dprender_gui/dprender_gui.h"
#include "../dprender_gui/dprender_gui_writelock.h"
#include "../../../dpgfx/dpgui_list/dpgui_list_readlock.h"
#include "../../../dpgfx/dpgui/dpgui.h"

namespace dp
{

    //ctor
    dprender_gui_list::dprender_gui_list( void ) : dpshared()
    {
        this->zeroList( this->glist, dprender_gui_list_max_gui );
    }

    //dtor
    dprender_gui_list::~dprender_gui_list( void )
    {
        this->deleteList( this->glist, dprender_gui_list_max_gui );
    }

    //generate readlock
    dpshared_readlock *dprender_gui_list::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_gui_list_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender_gui_list::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_gui_list_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender_gui_list::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_gui_list_ref( this, k, t_sync );
    }

    //zero list
    void dprender_gui_list::zeroList( dprender_gui **l, unsigned int cnt )
    {
        unsigned int i;

        for( i = 0; i < cnt; i++ )
            l[ i ] = 0;
    }

    //delete list
    void dprender_gui_list::deleteList( dprender_gui **l, unsigned int cnt )
    {
        unsigned int i;
        dprender_gui *p;

        for( i = 0; i < cnt; i++ )
        {
            p = l[ i ];
            if( !p )
                continue;
            delete p;
        }

        this->zeroList( l, cnt );
    }

    //add gui, starts task and takes ownership of gui, sets pointer to zero, use a ref to access
    bool dprender_gui_list::addGui( dprender_gui **ngui )
    {
        unsigned int i;
        dprender_gui *p;

        if( !ngui || !*ngui )
            return 0;

        for( i = 0; i < dprender_gui_list_max_gui; i++ )
        {
            p = this->glist[ i ];
            if( p )
                continue;

            p = *ngui;
            *ngui = 0;

            this->glist[ i ] = p;
        }

        delete *ngui;
        *ngui = 0;
        return 0;
    }

    //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
    unsigned int dprender_gui_list::getGuis( dprender_gui **glist, unsigned int max_cnt )
    {
        unsigned int i, j;
        dprender_gui *p;

        if( !glist )
            return 0;

        for( j = 0, i = 0; i < dprender_gui_list_max_gui; i++ )
        {
            p = this->glist[ i ];
            if( !p )
                continue;

            glist[ j ] = p;
            j++;
        }

        return j;
    }

    //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
    unsigned int dprender_gui_list::getGuisZSorted( dprender_gui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted )
    {
        unsigned int i, j, h, z;
        dprender_gui *p;

        if( !glist )
            return 0;

        j = h = z = 0;

        for( h = 0; h < this->max_z; h++ )
        {
            if( !bInverted )
                z = this->max_z - h;
            else
                z = h;

            for( i = 0; i < dprender_gui_list_max_gui; i++ )
            {
                p = this->glist[ i ];

                if( !p || p->getZ() != z )
                    continue;

                glist[ j ] = p;
                j++;
            }
        }

        return j;
    }

    //override to handle sync copy, be sure to call base class first!
    void dprender_gui_list::onSync( dpshared_readlock *psync )
    {
        dpgui_list_readlock *ll;
        dpgui *g, *glist[ dprender_gui_list_max_gui ];
        unsigned int i, m;
        dprender_gui * ng;

        this->dpshared::onSync( psync );

        if( !psync->isSyncType( "dpgui_list" ) )
            return;
        ll = (dpgui_list_readlock *)psync;

        m = ll->getGuis( glist, dprender_gui_list_max_gui );
        if( !m )
            return;

        for( i = 0; i < m; i++ )
        {
            g = glist[ i ];
            if( !g )
                continue;

            ng = new dprender_gui( g );
            if( !ng )
                continue;

            this->addGui( &ng );
        }
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dprender_gui_list::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( s.compare( "dprender_gui_list" ) )
            return 1;

        return this->dpshared::isSyncType( ctypename );
    }

    //override to handle processing
    void dprender_gui_list::onRun( dpshared_writelock *wl )
    {
        unsigned int i;
        dprender_gui *p;
        dprender_gui_writelock *pl;
        dpshared_guard g;

        this->dpshared::onRun( wl );

        for( i = 0; i < dprender_gui_list_max_gui; i++ )
        {
            p = this->glist[ i ];
            if( !p )
                continue;

            pl = (dprender_gui_writelock *)dpshared_guard_tryWriteLock_timeout( g, p, 30 );
            if( !pl )
                continue;

            pl->passContext( this->ctx );
            pl->run();

            g.release( pl );
        }
    }

    //pass in context
    void dprender_gui_list::passContext( dprender_gui_list_writelock *wl, dpapi_context_writelock *ctx )
    {
        this->ctx = ctx;
    }

    //render
    void dprender_gui_list::render( dprender_gui_list_writelock *wl, dpmatrix *m_parent, dpapi_context_writelock *ctx, dpapi_commandlist_writelock *cll )
    {
        unsigned int i;
        dprender_gui *p;
        dprender_gui_writelock *pl;
        dpshared_guard g;

        for( i = 0; i < dprender_gui_list_max_gui; i++ )
        {
            p = this->glist[ i ];
            if( !p )
                continue;

            pl = (dprender_gui_writelock *)dpshared_guard_tryWriteLock_timeout( g, p, 30 );
            if( !pl )
                continue;
            pl->render( m_parent, ctx, cll );

            g.release( pl );
        }
    }

}







