
/*
*/

#ifndef dprender_gui_list_h
#define dprender_gui_list_h

#include "../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dprender_gui_list_writelock;
    class dprender_gui;

    #define dprender_gui_list_max_gui 512

    class dprender_gui_list : public dpshared
    {

    private:

        dprender_gui *glist[ dprender_gui_list_max_gui ];
        unsigned int max_z, min_z;

        //zero list
        void zeroList( dprender_gui **l, unsigned int cnt );
        //delete list
        void deleteList( dprender_gui **l, unsigned int cnt );

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );
        //add gui, starts task and takes ownership of gui, sets pointer to zero, use a ref to access
        virtual bool addGui( dprender_gui **ngui );
        //get list of unsorted gui, returns count, second arg is size of static list passed in arg 1
        virtual unsigned int getGuis( dprender_gui **glist, unsigned int max_cnt );
        //get list of gui sorted by z order, returns count, second arg is size of static list passed in arg 1
        virtual unsigned int getGuisZSorted( dprender_gui **glist, unsigned int max_cnt, unsigned int &p_max_z, bool bInverted );

    public:

        //ctor
        dprender_gui_list( void );
        //dtor
        virtual ~dprender_gui_list( void );

        friend class dprender_gui_list_writelock;
        friend class dprender_gui_list_readlock;
    };

}

#endif






