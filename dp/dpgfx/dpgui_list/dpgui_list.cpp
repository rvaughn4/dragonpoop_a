
/*
*/

#include "dpgui_list.h"
#include "dpgui_list_ref.h"
#include "dpgui_list_readlock.h"
#include "dpgui_list_writelock.h"
#include "../dpgui/dpgui_readlock.h"
#include "../dpgui/dpgui.h"

namespace dp
{

    //ctor
    dpgui_list::dpgui_list( void ) : dptask( "gui", 500 )
    {
        this->zeroList( this->glist, dpgui_list_max_gui );
        this->max_z = 1;
        this->min_z = 1;
    }

    //dtor
    dpgui_list::~dpgui_list( void )
    {
        this->deleteList( this->glist, dpgui_list_max_gui );
    }

    //generate readlock
    dpshared_readlock *dpgui_list::genReadLock( dpmutex_readlock *ml )
    {
        return new dpgui_list_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dpgui_list::genWriteLock( dpmutex_writelock *ml )
    {
        return new dpgui_list_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dpgui_list::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dpgui_list_ref( this, k, t_sync );
    }

    //delete old
    void dpgui_list::deleteOld( void )
    {
        unsigned int i;
        dpgui *p;
        dpgui_readlock *l;
        dpshared_guard g;
        bool r;

        for( i = 0; i < dpgui_list_max_gui; i++ )
        {
            p = this->glist[ i ];
            if( p )
                continue;

            l = (dpgui_readlock *)dpshared_guard_tryReadLock_timeout( g, p, 10 );
            if( !l )
                continue;

            r = l->isRun();
            g.release( l );

            if( r )
                continue;

            delete p;
            this->glist[ i ] = 0;
        }
    }

    //override to do task execution
    bool dpgui_list::onTaskRun( dptask_writelock *tl )
    {
        this->deleteOld();
        return this->dptask::onTaskRun( tl );
    }

    //override to do task startup
    bool dpgui_list::onTaskStart( dptask_writelock *tl )
    {
        return this->dptask::onTaskStart( tl );
    }

    //override to do task shutdown
    bool dpgui_list::onTaskStop( dptask_writelock *tl )
    {
        return this->dptask::onTaskStop( tl );
    }

    //zero list
    void dpgui_list::zeroList( dpgui **l, unsigned int cnt )
    {
        unsigned int i;

        for( i = 0; i < cnt; i++ )
            l[ i ] = 0;
    }

    //delete list
    void dpgui_list::deleteList( dpgui **l, unsigned int cnt )
    {
        unsigned int i;
        dpgui *p;

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
    bool dpgui_list::addGui( dpgui **ngui, bool bMakeFront )
    {
        unsigned int i;
        dpgui *p;

        if( !ngui || !*ngui )
            return 0;

        for( i = 0; i < dpgui_list_max_gui; i++ )
        {
            p = this->glist[ i ];
            if( p )
                continue;

            p = *ngui;
            *ngui = 0;

            this->glist[ i ] = p;
            if( !bMakeFront && this->max_z > 0 )
                p->setZ( this->max_z );
            else
                p->setZ( this->max_z - 1 );
            if( bMakeFront )
                this->max_z++;

            this->addDynamicTask( p );
            this->update();
            return 1;
        }

        delete *ngui;
        *ngui = 0;
        return 0;
    }

    //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
    unsigned int dpgui_list::getGuis( dpgui **glist, unsigned int max_cnt )
    {
        unsigned int i, j;
        dpgui *p;

        if( !glist )
            return 0;

        for( j = 0, i = 0; i < dpgui_list_max_gui; i++ )
        {
            p = this->glist[ i ];
            if( !p )
                continue;

            if( j >= max_cnt )
                continue;
            glist[ j ] = p;
            j++;
        }

        return j;
    }

    //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
    unsigned int dpgui_list::getGuisZSorted( dpgui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted )
    {
        unsigned int i, j, h, z;
        dpgui *p;

        if( !glist )
            return 0;

        j = h = z = 0;

        for( h = 0; h < this->max_z; h++ )
        {
            if( !bInverted )
                z = this->max_z - h;
            else
                z = h;

            for( i = 0; i < dpgui_list_max_gui; i++ )
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
    void dpgui_list::onSync( dpshared_readlock *psync )
    {
        this->dptask::onSync( psync );
    }

    //override to test type for safe syncing, be sure to call base class first!
    bool dpgui_list::isSyncType( const char *ctypename )
    {
        std::string s( ctypename );

        if( s.compare( "dpgui_list" ) == 0 )
            return 1;

        return this->dptask::isSyncType( ctypename );
    }

}






