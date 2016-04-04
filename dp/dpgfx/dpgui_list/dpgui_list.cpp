
/*
*/

#include "dpgui_list.h"
#include "dpgui_list_ref.h"
#include "dpgui_list_readlock.h"
#include "dpgui_list_writelock.h"
#include "../dpgui/dpgui.h"

namespace dp
{

    //ctor
    dpgui_list::dpgui_list( void ) : dptask( "gui", 500 )
    {
        this->zeroList( this->glist, dpgui_list_max_gui );
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

    //override to do task execution
    bool dpgui_list::onTaskRun( dptask_writelock *tl )
    {
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

}






