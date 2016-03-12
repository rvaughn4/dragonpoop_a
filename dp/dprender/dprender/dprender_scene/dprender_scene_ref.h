
/*
allows the holding of a reference to a shared object without worrying about the lifetime of the object
object can be deleted while refs are still held
*/

#ifndef dprender_scene_ref_h
#define dprender_scene_ref_h

#include "../../../dpcore/dpshared/dpshared_ref.h"

namespace dp
{

    class dprender_scene;

    class dprender_scene_ref : public dpshared_ref
    {

    private:

        dprender_scene *p;

    protected:

        //dtor
        virtual ~dprender_scene_ref( void );

    public:

        //ctor
        dprender_scene_ref( dprender_scene *p, std::shared_ptr<dpshared_ref_kernel> *k, std::shared_ptr< std::atomic<uint64_t> > *t_sync );

        friend class dprender_scene;
    };

}

#endif








