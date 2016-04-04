
/*
*/

#ifndef dpgui_list_h
#define dpgui_list_h

#include "../../dpcore/dptask/dptask.h"

namespace dp
{

    class dpgui_list_writelock;
    class dpgui;

    #define dpgui_list_max_gui 512

    class dpgui_list : public dptask
    {

    private:

        dpgui *glist[ dpgui_list_max_gui ];

        //zero list
        void zeroList( dpgui **l, unsigned int cnt );
        //delete list
        void deleteList( dpgui **l, unsigned int cnt );

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

    public:

        //ctor
        dpgui_list( void );
        //dtor
        virtual ~dpgui_list( void );

        friend class dpgui_list_writelock;
        friend class dpgui_list_readlock;
    };

}

#endif





