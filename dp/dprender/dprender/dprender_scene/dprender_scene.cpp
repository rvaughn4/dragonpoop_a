
/*

*/

#include "dprender_scene.h"
#include "dprender_scene_ref.h"
#include "dprender_scene_readlock.h"
#include "dprender_scene_writelock.h"

namespace dp
{

    //ctor
    dprender_scene::dprender_scene( dprender_writelock *rl ) : dpshared()
    {
    }

    //dtor
    dprender_scene::~dprender_scene( void )
    {
    }

    //generate readlock
    dpshared_readlock *dprender_scene::genReadLock( dpmutex_readlock *ml )
    {
        return new dprender_scene_readlock( this, ml );
    }

    //generate writelock
    dpshared_writelock *dprender_scene::genWriteLock( dpmutex_writelock *ml )
    {
        return new dprender_scene_writelock( this, ml );
    }

    //generate ref
    dpshared_ref *dprender_scene::genRef( std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync )
    {
        return new dprender_scene_ref( this, k, t_sync );
    }

}








