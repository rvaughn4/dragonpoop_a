
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dprender_scene_thread_ref_h
#define dprender_scene_thread_ref_h

#include "../../../dpcore/dptask/dptask_ref.h"

namespace dp
{

    class dprender_scene_thread;

    class dprender_scene_thread_ref : public dptask_ref
    {

    private:

        dprender_scene_thread *p;

    protected:

        //dtor
        virtual ~dprender_scene_thread_ref( void );

    public:

        //ctor
        dprender_scene_thread_ref( dprender_scene_thread *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dprender_scene_thread;
    };

}

#endif









