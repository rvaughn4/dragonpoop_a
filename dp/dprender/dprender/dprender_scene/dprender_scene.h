
/*

*/

#ifndef dprender_scene_h
#define dprender_scene_h

#include "../../../dpcore/dpshared/dpshared.h"

namespace dp
{

    class dprender_scene_writelock;
    class dprender_writelock;

    class dprender_scene : public dpshared
    {

    private:

    protected:

        //generate readlock
        virtual dpshared_readlock *genReadLock( dpmutex_readlock *ml );
        //generate writelock
        virtual dpshared_writelock *genWriteLock( dpmutex_writelock *ml );
        //generate ref
        virtual dpshared_ref *genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

    public:

        //ctor
        dprender_scene( dprender_writelock *rl );
        //dtor
        virtual ~dprender_scene( void );

        friend class dprender_scene_writelock;
        friend class dprender_scene_readlock;
    };

}

#endif







