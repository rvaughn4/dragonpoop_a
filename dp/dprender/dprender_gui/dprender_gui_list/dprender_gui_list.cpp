
/*
*/

#include "dprender_gui_list.h"
#include "dprender_gui_list_ref.h"
#include "dprender_gui_list_readlock.h"
#include "dprender_gui_list_writelock.h"
#include "../dprender_gui/dprender_gui.h"

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

}







